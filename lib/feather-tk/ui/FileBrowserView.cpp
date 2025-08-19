// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/FileBrowserPrivate.h>

#include <feather-tk/ui/DrawUtil.h>

#include <feather-tk/core/File.h>
#include <feather-tk/core/Format.h>
#include <feather-tk/core/String.h>

#include <filesystem>
#include <optional>

namespace feather_tk
{
    namespace
    {
        const float doubleClickTime = .5F;

        struct FileBrowserItem
        {
            std::shared_ptr<Image> icon;
            std::vector<std::string> text;
            std::vector<Size2I> textSizes;
            Size2I size;
        };
    }

    struct FileBrowserView::Private
    {
        FileBrowserMode mode = FileBrowserMode::File;
        std::shared_ptr<FileBrowserModel> model;
        std::string search;
        std::vector<FileBrowserInfo> info;
        std::shared_ptr<ObservableValue<int> > current;
        std::vector<FileBrowserItem> items;
        std::function<void(const std::filesystem::path&)> callback;
        std::function<void(const std::filesystem::path&)> selectCallback;

        std::shared_ptr<ValueObserver<std::filesystem::path> > pathObserver;
        std::shared_ptr<ValueObserver<FileBrowserOptions> > optionsObserver;
        std::shared_ptr<ValueObserver<std::string> > extensionObserver;

        float iconScale = 1.F;
        std::shared_ptr<Image> directoryImage;
        std::shared_ptr<Image> fileImage;

        struct SizeData
        {
            std::optional<float> displayScale;
            int margin = 0;
            int border = 0;
            int pad = 0;
            FontInfo fontInfo;
            FontMetrics fontMetrics;
        };
        SizeData size;

        struct MouseData
        {
            int hover = 0;
            int pressed = 0;
            int click = 0;
            std::chrono::steady_clock::time_point clickTime;
        };
        MouseData mouse;
    };

    void FileBrowserView::_init(
        const std::shared_ptr<Context>& context,
        FileBrowserMode mode,
        const std::shared_ptr<FileBrowserModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "feather_tk::FileBrowserView", parent);
        FEATHER_TK_P();

        setAcceptsKeyFocus(true);
        setBackgroundRole(ColorRole::Base);
        _setMouseHoverEnabled(true);
        _setMousePressEnabled(true);

        p.mode = mode;
        p.model = model;
        p.current = ObservableValue<int>::create(-1);

        p.pathObserver = ValueObserver<std::filesystem::path>::create(
            model->observePath(),
            [this](const std::filesystem::path&)
            {
                _directoryUpdate();
            });

        p.optionsObserver = ValueObserver<FileBrowserOptions>::create(
            model->observeOptions(),
            [this](const FileBrowserOptions&)
            {
                _directoryUpdate();
            });

        p.extensionObserver = ValueObserver<std::string>::create(
            model->observeExtension(),
            [this](const std::string&)
            {
                _directoryUpdate();
            });
    }

    FileBrowserView::FileBrowserView() :
        _p(new Private)
    {}

    FileBrowserView::~FileBrowserView()
    {}

    std::shared_ptr<FileBrowserView> FileBrowserView::create(
        const std::shared_ptr<Context>& context,
        FileBrowserMode mode,
        const std::shared_ptr<FileBrowserModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<FileBrowserView>(new FileBrowserView);
        out->_init(context, mode, model, parent);
        return out;
    }

    void FileBrowserView::reload()
    {
        _directoryUpdate();
    }

    void FileBrowserView::setCallback(const std::function<void(const std::filesystem::path&)>& value)
    {
        _p->callback = value;
    }

    void FileBrowserView::setSelectCallback(const std::function<void(const std::filesystem::path&)>& value)
    {
        _p->selectCallback = value;
    }

    void FileBrowserView::setSearch(const std::string& value)
    {
        FEATHER_TK_P();
        if (value == p.search)
            return;
        p.search = value;
        _directoryUpdate();
    }

    std::shared_ptr<IObservableValue<int> > FileBrowserView::observeCurrent() const
    {
        return _p->current;
    }

    Box2I FileBrowserView::getRect(int index) const
    {
        FEATHER_TK_P();
        int y = 0;
        int i = 0;
        for (; i < index && i < p.items.size(); ++i)
        {
            const FileBrowserItem& item = p.items[i];
            y += item.size.h;
        }
        int h = 0;
        if (i < p.items.size())
        {
            h = p.items[i].size.h;
        }
        return Box2I(0, y, getGeometry().w(), h);
    }

    void FileBrowserView::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        FEATHER_TK_P();

        if (event.displayScale != p.iconScale)
        {
            p.iconScale = event.displayScale;
            p.directoryImage.reset();
            p.fileImage.reset();
        }
        if (!p.directoryImage)
        {
            p.directoryImage = event.iconSystem->get("Directory", event.displayScale);
        }
        if (!p.fileImage)
        {
            p.fileImage = event.iconSystem->get("File", event.displayScale);
        }

        if (!p.size.displayScale.has_value() ||
            (p.size.displayScale.has_value() && p.size.displayScale.value() != event.displayScale))
        {
            p.size.displayScale = event.displayScale;
            p.size.margin = event.style->getSizeRole(SizeRole::MarginInside, event.displayScale);
            p.size.border = event.style->getSizeRole(SizeRole::Border, event.displayScale);
            p.size.pad = event.style->getSizeRole(SizeRole::LabelPad, event.displayScale);
            p.size.fontInfo = event.style->getFontRole(FontRole::Label, event.displayScale);
            p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
            for (size_t i = 0; i < p.info.size() && i < p.items.size(); ++i)
            {
                auto& item = p.items[i];
                item.icon = p.info[i].isDir ? p.directoryImage : p.fileImage;
                item.size = item.icon ? item.icon->getSize() : Size2I();
                item.textSizes.clear();
                for (const auto& text : item.text)
                {
                    const Size2I textSize = event.fontSystem->getSize(text, p.size.fontInfo);
                    item.textSizes.push_back(textSize);
                    item.size.w += textSize.w + p.size.pad * 2 + p.size.margin * 2;
                    item.size.h = std::max(item.size.h, textSize.h) + p.size.margin * 2;
                }
            }
        }

        Size2I sizeHint;
        for (const auto& item : p.items)
        {
            sizeHint.w = std::max(sizeHint.w, item.size.w);
            sizeHint.h += item.size.h;
        }
        _setSizeHint(sizeHint);
    }

    void FileBrowserView::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IWidget::drawEvent(drawRect, event);
        FEATHER_TK_P();
        const Box2I& g = getGeometry();

        // Draw the current state.
        if (p.current->get() != -1 && hasKeyFocus())
        {
            const Box2I g2 = move(getRect(p.current->get()), g.min);
            event.render->drawMesh(
                border(g2, p.size.border),
                event.style->getColorRole(ColorRole::KeyFocus));
        }

        // Draw the mouse hover.
        if (p.mouse.hover != 0)
        {
            const Box2I g2 = move(getRect(p.mouse.hover), g.min);
            event.render->drawRect(
                g2,
                event.style->getColorRole(ColorRole::Hover));
        }

        // Draw the items.
        int y = g.min.y;
        for (const auto& item : p.items)
        {
            int x = g.min.x;
            const Box2I g2(x, y, item.size.w, item.size.h);
            if (intersects(g2, drawRect))
            {
                if (item.icon)
                {
                    const Size2I& iconSize = item.icon->getSize();
                    event.render->drawImage(
                        item.icon,
                        Box2I(
                            x,
                            y + item.size.h / 2 - iconSize.h / 2,
                            iconSize.w,
                            iconSize.h),
                        event.style->getColorRole(ColorRole::Text));
                    x += iconSize.w;
                }
                int rightColumnsSize = 0;
                for (int i = 1; i < item.text.size() && i < item.textSizes.size(); ++i)
                {
                    rightColumnsSize += item.textSizes[i].w + p.size.pad * 2 + p.size.margin * 2;
                }
                for (int i = 0; i < item.text.size() && i < item.textSizes.size(); ++i)
                {
                    const auto glyphs = event.fontSystem->getGlyphs(item.text[i], p.size.fontInfo);
                    event.render->drawText(
                        glyphs,
                        p.size.fontMetrics,
                        V2I(x + p.size.pad + p.size.margin, y + item.size.h / 2 - item.textSizes[i].h / 2),
                        event.style->getColorRole(isEnabled() ?
                            ColorRole::Text :
                            ColorRole::TextDisabled));
                    if (0 == i)
                    {
                        x = g.max.x - rightColumnsSize;
                    }
                    else
                    {
                        x += item.textSizes[i].w + +p.size.pad * 2 + p.size.margin * 2;
                    }
                }
            }
            y += item.size.h;
        }
    }

    void FileBrowserView::mouseEnterEvent(MouseEnterEvent& event)
    {
        IWidget::mouseEnterEvent(event);
        FEATHER_TK_P();
        const int hover = _getItem(event.pos);
        if (hover != p.mouse.hover)
        {
            p.mouse.hover = hover;
            _setDrawUpdate();
        }
    }

    void FileBrowserView::mouseLeaveEvent()
    {
        IWidget::mouseLeaveEvent();
        FEATHER_TK_P();
        int hover = 0;
        if (hover != p.mouse.hover)
        {
            p.mouse.hover = hover;
            _setDrawUpdate();
        }
    }

    void FileBrowserView::mouseMoveEvent(MouseMoveEvent& event)
    {
        IWidget::mouseMoveEvent(event);
        FEATHER_TK_P();
        const int hover = _getItem(event.pos);
        if (hover != p.mouse.hover)
        {
            p.mouse.hover = hover;
            _setDrawUpdate();
        }
    }

    void FileBrowserView::mousePressEvent(MouseClickEvent& event)
    {
        IWidget::mousePressEvent(event);
        FEATHER_TK_P();
        takeKeyFocus();
        const int hover = _getItem(event.pos);
        if (hover != p.mouse.hover)
        {
            p.mouse.hover = hover;
            _setDrawUpdate();
        }
        if (p.mouse.hover != 0)
        {
            _setCurrent(p.mouse.hover);
            p.mouse.pressed = p.mouse.hover;
            _setDrawUpdate();
        }
    }

    void FileBrowserView::mouseReleaseEvent(MouseClickEvent& event)
    {
        IWidget::mouseReleaseEvent(event);
        FEATHER_TK_P();
        const Box2I& g = getGeometry();
        if (p.mouse.pressed != 0)
        {
            if (contains(getRect(p.mouse.pressed), event.pos - g.min))
            {
                const auto now = std::chrono::steady_clock::now();
                const std::chrono::duration<float> diff = now - p.mouse.clickTime;
                if (p.mouse.click == p.mouse.pressed && diff.count() < doubleClickTime)
                {
                    _doubleClick(p.mouse.pressed);
                }
                p.mouse.click = p.mouse.pressed;
                p.mouse.clickTime = now;
            }
            p.mouse.pressed = 0;
            _setDrawUpdate();
        }
    }

    void FileBrowserView::keyFocusEvent(bool value)
    {
        IWidget::keyFocusEvent(value);
        _setDrawUpdate();
    }

    void FileBrowserView::keyPressEvent(KeyEvent& event)
    {
        FEATHER_TK_P();
        if (0 == event.modifiers)
        {
            switch (event.key)
            {
            case Key::Up:
                event.accept = true;
                if (!hasKeyFocus())
                {
                    takeKeyFocus();
                    _setCurrent(p.mouse.hover);
                }
                else
                {
                    _setCurrent(p.current->get() - 1);
                }
                break;
            case Key::Down:
                event.accept = true;
                if (!hasKeyFocus())
                {
                    takeKeyFocus();
                    _setCurrent(p.mouse.hover);
                }
                else
                {
                    _setCurrent(p.current->get() + 1);
                }
                break;
            case Key::Home:
                event.accept = true;
                takeKeyFocus();
                _setCurrent(0);
                break;
            case Key::End:
                event.accept = true;
                takeKeyFocus();
                _setCurrent(static_cast<int>(p.info.size()) - 1);
                break;
            case Key::Return:
                event.accept = true;
                takeKeyFocus();
                _doubleClick(p.current->get());
                break;
            case Key::Escape:
                if (hasKeyFocus())
                {
                    event.accept = true;
                    releaseKeyFocus();
                }
                break;
            default: break;
            }
        }
        if (!event.accept)
        {
            IWidget::keyPressEvent(event);
        }
    }

    void FileBrowserView::keyReleaseEvent(KeyEvent& event)
    {
        IWidget::keyReleaseEvent(event);
        event.accept = true;
    }

    int FileBrowserView::_getItem(const V2I& value) const
    {
        FEATHER_TK_P();
        int out = -1;
        const Box2I& g = getGeometry();
        int y = 0;
        for (size_t i = 0; i < p.items.size(); ++i)
        {
            const auto& item = p.items[i];
            const Box2I g2(g.min.x, g.min.y + y, g.w(), item.size.h);
            if (contains(g2, value))
            {
                out = i;
                break;
            }
            y += item.size.h;
        }
        return out;
    }

    namespace
    {
        void list(
            FileBrowserMode mode,
            const std::filesystem::path& path,
            const FileBrowserOptions& options,
            const std::string& extension,
            const std::string& search,
            std::vector<FileBrowserInfo>& out)
        {
            try
            {
                for (const auto& i : std::filesystem::directory_iterator(path))
                {
                    const std::filesystem::path& path = i.path();
                    const std::string fileName = path.filename().u8string();

                    bool keep = true;
                    if (keep && !options.hidden && isDotFile(fileName))
                    {
                        keep = false;
                    }
                    const bool isDir = std::filesystem::is_directory(path);
                    if (keep && !isDir && !extension.empty())
                    {
                        keep = compare(
                            extension,
                            path.extension().u8string(),
                            CaseCompare::Insensitive);
                    }
                    if (keep && !search.empty())
                    {
                        keep = contains(
                            fileName,
                            search,
                            CaseCompare::Insensitive);
                    }
                    if (keep && FileBrowserMode::Dir == mode && !isDir)
                    {
                        keep = false;
                    }

                    if (keep)
                    {
                        out.push_back({
                            path,
                            isDir,
                            isDir ? 0 : std::filesystem::file_size(path),
                            std::filesystem::last_write_time(path) });
                    }
                }
            }
            catch (const std::exception&)
            {}

            std::function<int(const FileBrowserInfo& a, const FileBrowserInfo& b)> sort;
            switch (options.sort)
            {
            case FileBrowserSort::Name:
                sort = [](const FileBrowserInfo& a, const FileBrowserInfo& b)
                    {
                        return a.path.filename() < b.path.filename();
                    };
                break;
            case FileBrowserSort::Extension:
                sort = [](const FileBrowserInfo& a, const FileBrowserInfo& b)
                    {
                        return a.path.extension() < b.path.extension();
                    };
                break;
            case FileBrowserSort::Size:
                sort = [](const FileBrowserInfo& a, const FileBrowserInfo& b)
                    {
                        return a.size < b.size;
                    };
                break;
            case FileBrowserSort::Time:
                sort = [](const FileBrowserInfo& a, const FileBrowserInfo& b)
                    {
                        return a.time < b.time;
                    };
                break;
            default: break;
            }
            if (sort)
            {
                if (options.reverseSort)
                {
                    std::sort(out.rbegin(), out.rend(), sort);
                }
                else
                {
                    std::sort(out.begin(), out.end(), sort);
                }
            }
            std::stable_sort(
                out.begin(),
                out.end(),
                [](const FileBrowserInfo& a, const FileBrowserInfo& b)
                {
                    return a.isDir > b.isDir;
                });
        }
    }

    void FileBrowserView::_directoryUpdate()
    {
        FEATHER_TK_P();
        p.info.clear();
        p.items.clear();
        list(
            p.mode,
            p.model->getPath(),
            p.model->getOptions(),
            p.model->getExtension(),
            p.search,
            p.info);
        if (auto context = getContext())
        {
            for (size_t i = 0; i < p.info.size(); ++i)
            {
                const FileBrowserInfo& info = p.info[i];
                FileBrowserItem item;

                // File name.
                std::string text = info.path.filename().u8string();
                item.text.push_back(text);

                // File extension.
                text = !info.isDir ?
                    info.path.extension().u8string() :
                    std::string();
                item.text.push_back(text);

                // File size.
                if (!info.isDir)
                {
                    if (info.size < megabyte)
                    {
                        text = Format("{0}KB").
                            arg(info.size / static_cast<float>(kilobyte), 2);
                    }
                    else if (info.size < gigabyte)
                    {
                        text = Format("{0}MB").
                            arg(info.size / static_cast<float>(megabyte), 2);
                    }
                    else
                    {
                        text = Format("{0}GB").
                            arg(info.size / static_cast<float>(gigabyte), 2);
                    }
                    item.text.push_back(text);
                }

                // File last modification time.
                // \todo std::format is available in C++20.
                //text = std::format("{}", info.time);

                p.items.push_back(item);
            }
        }

        p.current->setIfChanged(-1);
        if (p.selectCallback)
        {
            p.selectCallback(std::filesystem::path());
        }

        _setSizeUpdate();
        _setDrawUpdate();
        p.size.displayScale.reset();
    }

    void FileBrowserView::_setCurrent(int index)
    {
        FEATHER_TK_P();
        const int tmp = !p.info.empty() ?
            clamp(index, 0, static_cast<int>(p.info.size()) - 1) :
            -1;
        std::filesystem::path path;
        if (tmp != -1)
        {
            path = p.info[tmp].path;
        }
        if (p.current->setIfChanged(tmp))
        {
            if (p.selectCallback)
            {
                p.selectCallback(path);
            }
            _setDrawUpdate();
        }
    }

    void FileBrowserView::_doubleClick(int index)
    {
        FEATHER_TK_P();
        takeKeyFocus();
        if (index >= 0 && index < p.info.size())
        {
            const FileBrowserInfo info = p.info[index];
            switch (p.mode)
            {
            case FileBrowserMode::File:
                if (!info.isDir && p.callback)
                {
                    p.callback(info.path);
                }
                else if (info.isDir)
                {
                    p.model->setPath(info.path);
                }
                break;
            case FileBrowserMode::Dir:
                if (info.isDir)
                {
                    p.model->setPath(info.path);
                }
                break;
            default: break;
            }
        }
    }
}