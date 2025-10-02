// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/UI/TextEditPrivate.h>

#include <ftk/UI/App.h>
#include <ftk/UI/ClipboardSystem.h>
#include <ftk/UI/DrawUtil.h>
#include <ftk/UI/IWindow.h>
#include <ftk/UI/LayoutUtil.h>
#include <ftk/UI/ScrollArea.h>

#include <ftk/Core/RenderUtil.h>

#include <optional>

namespace ftk
{
    struct TextEditWidget::Private
    {
        TextEditOptions options;
        std::shared_ptr<TextEditModel> model;
        std::function<void(const std::vector<std::string>&)> textCallback;
        std::function<void(bool)> focusCallback;
        bool cursorVisible = false;
        std::chrono::steady_clock::time_point cursorTimer;
        TextEditSelection selection;
        std::shared_ptr<FontSystem> fontSystem;

        struct SizeData
        {
            std::optional<float> displayScale;
            int margin = 0;
            int border = 0;
            FontInfo fontInfo;
            FontMetrics fontMetrics;
            Size2I textSize;
        };
        SizeData size;

        std::shared_ptr<ListObserver<std::string> > textObserver;
        std::shared_ptr<ValueObserver<TextEditPos> > cursorObserver;
        std::shared_ptr<ValueObserver<TextEditSelection> > selectionObserver;
    };

    void TextEditWidget::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<TextEditModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "ftk::TextEditWidget", parent);
        FTK_P();

        setAcceptsKeyFocus(true);
        _setMouseHoverEnabled(true);
        _setMousePressEnabled(true);

        p.model = model;
        
        p.fontSystem = context->getSystem<FontSystem>();

        p.textObserver = ListObserver<std::string>::create(
            p.model->observeText(),
            [this](const std::vector<std::string>& value)
            {
                FTK_P();
                if (p.textCallback)
                {
                    p.textCallback(value);
                }
                p.size.displayScale.reset();
                _setSizeUpdate();
                _setDrawUpdate();
            });

        p.cursorObserver = ValueObserver<TextEditPos>::create(
            p.model->observeCursor(),
            [this](const TextEditPos&)
            {
                _cursorReset();
                _setDrawUpdate();
            });

        p.selectionObserver = ValueObserver<TextEditSelection>::create(
            p.model->observeSelection(),
            [this](const TextEditSelection& value)
            {
                _p->selection = value;
                _setDrawUpdate();
            });
    }

    TextEditWidget::TextEditWidget() :
        _p(new Private)
    {}

    TextEditWidget::~TextEditWidget()
    {}

    std::shared_ptr<TextEditWidget> TextEditWidget::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<TextEditModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<TextEditWidget>(new TextEditWidget);
        out->_init(context, model, parent);
        return out;
    }

    const std::vector<std::string>& TextEditWidget::getText() const
    {
        return _p->model->getText();
    }

    void TextEditWidget::setText(const std::vector<std::string>& value)
    {
        _p->model->setText(value);
    }

    void TextEditWidget::clearText()
    {
        _p->model->clearText();
    }

    void TextEditWidget::setTextCallback(const std::function<void(const std::vector<std::string>&)>& value)
    {
        _p->textCallback = value;
    }

    void TextEditWidget::setFocusCallback(const std::function<void(bool)>& value)
    {
        _p->focusCallback = value;
    }

    void TextEditWidget::selectAll()
    {
        _p->model->selectAll();
    }

    void TextEditWidget::clearSelection()
    {
        _p->model->clearSelection();
    }

    void TextEditWidget::setOptions(const TextEditOptions& value)
    {
        FTK_P();
        if (value == p.options)
            return;
        p.options = value;
        p.size.displayScale.reset();
        _setSizeUpdate();
        _setDrawUpdate();
    }

    Box2I TextEditWidget::getCursorBox(bool margin) const
    {
        FTK_P();
        const auto& text = p.model->getText();
        const TextEditPos& cursor = p.model->getCursor();
        V2I pos(p.size.margin, 0);
        pos.y += p.size.fontMetrics.lineHeight * cursor.line;
        if (cursor.line >= 0 && cursor.line < text.size())
        {
            const std::string& line = text[cursor.line];
            pos.x += p.fontSystem->getSize(line.substr(0, cursor.chr), p.size.fontInfo).w;
        }
        Box2I out(pos.x, pos.y, p.size.border, p.size.fontMetrics.lineHeight);
        if (margin)
        {
            out = ftk::margin(out, p.size.margin, 0, p.size.margin, 0);
        }
        return out;
    }

    void TextEditWidget::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        FTK_P();
        if (auto parent = getParentT<ScrollArea>())
        {
            const Size2I size = parent->getGeometry().size();
            p.model->setPageRows(size.h / p.size.fontMetrics.lineHeight);
        }
    }

    void TextEditWidget::setVisible(bool value)
    {
        FTK_P();
        const bool changed = value != isVisible(false);
        IWidget::setVisible(value);
        if (changed && !isVisible(false))
        {
            if (p.cursorVisible)
            {
                p.cursorVisible = false;
                _setDrawUpdate();
            }
        }
    }

    void TextEditWidget::setEnabled(bool value)
    {
        FTK_P();
        const bool changed = value != isEnabled(false);
        IWidget::setEnabled(value);
        if (changed && !isEnabled(false))
        {
            if (p.cursorVisible)
            {
                p.cursorVisible = false;
                _setDrawUpdate();
            }
        }
    }

    void TextEditWidget::tickEvent(
        bool parentsVisible,
        bool parentsEnabled,
        const TickEvent& event)
    {
        IWidget::tickEvent(parentsVisible, parentsEnabled, event);
        FTK_P();
        if (hasKeyFocus())
        {
            const auto now = std::chrono::steady_clock::now();
            const std::chrono::duration<float> diff = now - p.cursorTimer;
            if (diff.count() > .5F)
            {
                p.cursorVisible = !p.cursorVisible;
                _setDrawUpdate();
                p.cursorTimer = now;
            }
        }
        else if (p.cursorVisible)
        {
            p.cursorVisible = false;
            _setDrawUpdate();
        }
    }

    void TextEditWidget::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        FTK_P();

        if (!p.size.displayScale.has_value() ||
            (p.size.displayScale.has_value() && p.size.displayScale.value() != event.displayScale))
        {
            p.size.displayScale = event.displayScale;
            p.size.margin = event.style->getSizeRole(SizeRole::MarginInside, event.displayScale);
            p.size.border = event.style->getSizeRole(SizeRole::Border, event.displayScale);
            p.size.fontInfo = event.style->getFontRole(p.options.fontRole, event.displayScale);
            p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
            p.size.textSize = Size2I();
            for (const auto& line : p.model->getText())
            {
                p.size.textSize.w = std::max(
                    event.fontSystem->getSize(line, p.size.fontInfo).w,
                    p.size.textSize.w);
                p.size.textSize.h += p.size.fontMetrics.lineHeight;
            }
        }

        _setSizeHint(margin(p.size.textSize, p.size.margin, 0));
    }

    void TextEditWidget::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IWidget::drawEvent(drawRect, event);
        FTK_P();

        const Box2I& g = getGeometry();

        // Draw the background.
        event.render->drawRect(
            g,
            event.style->getColorRole(ColorRole::Base));

        //event.render->drawMesh(
        //    border(g, 1),
        //    event.style->getColorRole(ColorRole::Text));

        // Draw the selection.
        const Box2I g2 = margin(g, -p.size.margin, 0, -p.size.margin, 0);
        const auto& text = p.model->getText();
        if (p.selection.isValid() &&
            p.selection.first.line >= 0 &&
            p.selection.first.line < static_cast<int>(text.size()) &&
            p.selection.second.line >= 0 &&
            p.selection.second.line < static_cast<int>(text.size()))
        {
            std::vector<Box2I> boxes;
            const TextEditPos min = p.selection.min();
            const TextEditPos max = p.selection.max();
            if (min.line == max.line)
            {
                const std::string& line = text[min.line];
                const int w0 = event.fontSystem->getSize(line.substr(0, min.chr), p.size.fontInfo).w;
                const int w1 = event.fontSystem->getSize(line.substr(0, max.chr), p.size.fontInfo).w;
                boxes.push_back(Box2I(
                    g2.min.x + w0,
                    g2.min.y + min.line * p.size.fontMetrics.lineHeight,
                    w1 - w0,
                    p.size.fontMetrics.lineHeight));
            }
            else
            {
                int w0 = event.fontSystem->getSize(text[min.line].substr(0, min.chr), p.size.fontInfo).w;
                int w1 = event.fontSystem->getSize(text[min.line], p.size.fontInfo).w;
                boxes.push_back(Box2I(
                    g2.min.x + w0,
                    g2.min.y + min.line * p.size.fontMetrics.lineHeight,
                    w1 - w0,
                    p.size.fontMetrics.lineHeight));
                for (int i = min.line + 1; i < max.line; ++i)
                {
                    w0 = event.fontSystem->getSize(text[i], p.size.fontInfo).w;
                    boxes.push_back(Box2I(
                        g2.min.x,
                        g2.min.y + i * p.size.fontMetrics.lineHeight,
                        w0,
                        p.size.fontMetrics.lineHeight));
                }
                w0 = event.fontSystem->getSize(text[max.line].substr(0, max.chr), p.size.fontInfo).w;
                boxes.push_back(Box2I(
                    g2.min.x,
                    g2.min.y + max.line * p.size.fontMetrics.lineHeight,
                    w0,
                    p.size.fontMetrics.lineHeight));
            }
            for (const auto& box : boxes)
            {
                if (intersects(box, drawRect))
                {
                    event.render->drawRect(box, event.style->getColorRole(ColorRole::Checked));
                }
            }
        }

        // Draw the text.
        const bool enabled = isEnabled();
        V2I pos(g2.min);
        for (const auto& line : text)
        {
            const Box2I g3(pos.x, pos.y, p.size.textSize.w, p.size.fontMetrics.lineHeight);
            if (intersects(g3, drawRect))
            {
                const auto glyphs = event.fontSystem->getGlyphs(line, p.size.fontInfo);
                event.render->drawText(
                    glyphs,
                    p.size.fontMetrics,
                    pos,
                    event.style->getColorRole(enabled ?
                        ColorRole::Text :
                        ColorRole::TextDisabled));
            }
            pos.y += p.size.fontMetrics.lineHeight;
        }

        // Draw the cursor.
        if (p.cursorVisible)
        {
            const Box2I cursor = getCursorBox();
            event.render->drawRect(
                Box2I(g.min.x + cursor.min.x, g.min.y + cursor.min.y, cursor.w(), cursor.h()),
                event.style->getColorRole(ColorRole::Text));
        }
    }

    void TextEditWidget::mouseMoveEvent(MouseMoveEvent& event)
    {
        IWidget::mouseMoveEvent(event);
        FTK_P();
        /*if (_isMousePressed())
        {
            const int cursorPos = _getCursorPos(event.pos);
            if (cursorPos != p.cursorPos)
            {
                p.cursorPos = cursorPos;
                p.cursorVisible = true;
                p.cursorTimer = std::chrono::steady_clock::now();
                _setDrawUpdate();
            }
            if (cursorPos != p.selection.get().second)
            {
                p.selection.setSecond(cursorPos);
                _setDrawUpdate();
            }
        }*/
    }

    void TextEditWidget::mousePressEvent(MouseClickEvent& event)
    {
        IWidget::mousePressEvent(event);
        FTK_P();
        /*const int cursorPos = _getCursorPos(event.pos);
        if (cursorPos != p.cursorPos)
        {
            p.cursorPos = cursorPos;
            p.cursorVisible = true;
            p.cursorTimer = std::chrono::steady_clock::now();
            _setDrawUpdate();
        }
        const SelectionPair selection(cursorPos, cursorPos);
        if (selection != p.selection.get())
        {
            p.selection.set(selection);
            _setDrawUpdate();
        }*/
        takeKeyFocus();
    }

    void TextEditWidget::keyFocusEvent(bool value)
    {
        IWidget::keyFocusEvent(value);
        FTK_P();
        if (!value)
        {
            p.model->clearSelection();
        }
        if (p.focusCallback)
        {
            p.focusCallback(value);
        }
    }

    void TextEditWidget::keyPressEvent(KeyEvent& event)
    {
        FTK_P();
        if (hasKeyFocus())
        {
            event.accept = p.model->key(event.key, event.modifiers);
        }
        if (!event.accept)
        {
            IWidget::keyPressEvent(event);
        }
    }

    void TextEditWidget::keyReleaseEvent(KeyEvent& event)
    {
        IWidget::keyReleaseEvent(event);
        event.accept = true;
    }

    void TextEditWidget::textEvent(TextEvent& event)
    {
        IWidget::textEvent(event);
        event.accept = true;
        _p->model->text(event.text);
    }

    TextEditPos TextEditWidget::_getCursorPos(const V2I& value) const
    {
        return TextEditPos();
    }

    void TextEditWidget::_cursorReset()
    {
        FTK_P();
        p.cursorVisible = true;
        p.cursorTimer = std::chrono::steady_clock::now();
    }
}