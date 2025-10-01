// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/UI/TextEditPrivate.h>

#include <ftk/UI/App.h>
#include <ftk/UI/ClipboardSystem.h>
#include <ftk/UI/DrawUtil.h>
#include <ftk/UI/IWindow.h>
#include <ftk/UI/LayoutUtil.h>

#include <ftk/Core/RenderUtil.h>

#include <optional>

namespace ftk
{
    struct TextEditWidget::Private
    {
        std::shared_ptr<TextEditModel> model;
        std::function<void(const std::vector<std::string>&)> textCallback;
        std::function<void(bool)> focusCallback;
        FontRole fontRole = FontRole::Label;
        bool cursorVisible = false;
        std::chrono::steady_clock::time_point cursorTimer;
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
        std::shared_ptr<ValueObserver<TextPos> > cursorObserver;
        std::shared_ptr<ValueObserver<Selection> > selectionObserver;
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

        _textUpdate();

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

        p.cursorObserver = ValueObserver<TextPos>::create(
            p.model->observeCursor(),
            [this](const TextPos&)
            {
                _cursorReset();
                _setDrawUpdate();
            });

        p.selectionObserver = ValueObserver<Selection>::create(
            p.model->observeSelection(),
            [this](const Selection&)
            {
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

    void TextEditWidget::selectNone()
    {
        _p->model->selectNone();
    }

    FontRole TextEditWidget::getFontRole() const
    {
        return _p->fontRole;
    }

    void TextEditWidget::setFontRole(FontRole value)
    {
        FTK_P();
        if (value == p.fontRole)
            return;
        p.fontRole = value;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    Box2I TextEditWidget::getCursorBox(bool margin) const
    {
        FTK_P();
        const auto& text = p.model->getText();
        const TextPos& cursor = p.model->getCursor();
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
            p.size.fontInfo = event.style->getFontRole(p.fontRole, event.displayScale);
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
        /*if (p.selection.isValid())
        {
            const auto selection = p.selection.getSorted();
            const std::string text0 = p.text.substr(0, selection.first);
            const int x0 = event.fontSystem->getSize(text0, p.size.fontInfo).w;
            const std::string text1 = p.text.substr(0, selection.second);
            const int x1 = event.fontSystem->getSize(text1, p.size.fontInfo).w;
            event.render->drawRect(
                Box2I(p.draw->g3.x() + x0, p.draw->g3.y(), x1 - x0 + 1, p.draw->g3.h()),
                event.style->getColorRole(ColorRole::Checked));
        }*/

        // Draw the text.
        const bool enabled = isEnabled();
        const Box2I g2 = margin(g, -p.size.margin, 0, -p.size.margin, 0);
        V2I pos(g2.min);
        for (const auto& line : p.model->getText())
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
            //const Size2I lineSize = event.fontSystem->getSize(line, p.size.fontInfo);

            //p.draw->glyphs = event.fontSystem->getGlyphs(p.text, p.size.fontInfo);
            //p.draw->glyphsBox = event.fontSystem->getBox(p.text, p.size.fontInfo);
        }
        /*const V2I pos(
            p.draw->g3.x(),
            p.draw->g3.y() + p.draw->g3.h() / 2 - p.size.fontMetrics.lineHeight / 2);
        if (!p.text.empty() && p.draw->glyphs.empty())
        {
            p.draw->glyphs = event.fontSystem->getGlyphs(p.text, p.size.fontInfo);
            p.draw->glyphsBox = event.fontSystem->getBox(p.text, p.size.fontInfo);
        }
        event.render->drawText(
            p.draw->glyphs,
            p.size.fontMetrics,
            pos,
            event.style->getColorRole(enabled ?
                ColorRole::Text :
                ColorRole::TextDisabled));*/

        // Draw the cursor.
        if (p.cursorVisible)
        {
            /*const std::vector<std::string>& text = p.model->getText();
            const TextPos& cursorPos = p.model->getCursor();
            V2I pos(g2.min);
            if (cursorPos.line >= 0 && cursorPos.line < text.size())
            {
                pos.y += p.size.fontMetrics.lineHeight * cursorPos.line;
                const std::string& line = text[cursorPos.line];
                const auto glyphBoxes = event.fontSystem->getBox(line, p.size.fontInfo);
                if (cursorPos.chr >= 0 && cursorPos.chr < glyphBoxes.size())
                {
                    pos.x += glyphBoxes[cursorPos.chr].min.x;
                }
                else if (cursorPos.chr == line.size() && !glyphBoxes.empty())
                {
                    pos.x += glyphBoxes.back().min.x + glyphBoxes.back().w();
                }
            }*/
            const Box2I cursor = getCursorBox();
            event.render->drawRect(
                Box2I(g.min.x + cursor.min.x, g.min.y + cursor.min.y, cursor.w(), cursor.h()),
                event.style->getColorRole(ColorRole::Text));

            /*const std::string text = p.text.substr(0, p.cursorPos);
            const int x = event.fontSystem->getSize(text, p.size.fontInfo).w;
            event.render->drawRect(
                Box2I(
                    p.draw->g3.x() + x,
                    p.draw->g3.y(),
                    p.size.border,
                    p.draw->g3.h()),
                event.style->getColorRole(ColorRole::Text));*/
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
            p.model->selectNone();
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
            event.accept = p.model->key(event.key);
        }
        /*if (hasKeyFocus())
        {
            switch (event.key)
            {
            case Key::A:
                event.accept = true;
                if (event.modifiers & static_cast<int>(KeyModifier::Control))
                {
                    selectAll();
                }
                break;
            case Key::C:
                event.accept = true;
                if (event.modifiers & static_cast<int>(KeyModifier::Control))
                {
                    if (p.selection.isValid())
                    {
                        if (auto context = getContext())
                        {
                            const auto selection = p.selection.getSorted();
                            const std::string text = p.text.substr(
                                selection.first,
                                selection.second - selection.first);
                            auto clipboardSystem = context->getSystem<ClipboardSystem>();
                            clipboardSystem->setText(text);
                        }
                    }
                }
                break;
            case Key::V:
                event.accept = true;
                if (event.modifiers & static_cast<int>(KeyModifier::Control))
                {
                    if (auto context = getContext())
                    {
                        auto clipboardSystem = context->getSystem<ClipboardSystem>();
                        const std::string text = clipboardSystem->getText();
                        if (p.selection.isValid())
                        {
                            const auto selection = p.selection.getSorted();
                            p.text.replace(
                                selection.first,
                                selection.second - selection.first,
                                text);
                            p.selection.clear();
                            p.cursorPos = selection.first + text.size();
                        }
                        else
                        {
                            p.text.insert(p.cursorPos, text);
                            p.cursorPos += text.size();
                        }
                        if (p.textChangedCallback)
                        {
                            p.textChangedCallback(p.text);
                        }
                        _textUpdate();
                    }
                }
                break;
            case Key::X:
                event.accept = true;
                if (event.modifiers & static_cast<int>(KeyModifier::Control))
                {
                    if (p.selection.isValid())
                    {
                        if (auto context = getContext())
                        {
                            const auto selection = p.selection.getSorted();
                            const std::string text = p.text.substr(
                                selection.first,
                                selection.second - selection.first);
                            auto clipboardSystem = context->getSystem<ClipboardSystem>();
                            clipboardSystem->setText(text);
                            p.text.replace(
                                selection.first,
                                selection.second - selection.first,
                                "");
                            p.selection.clear();
                            p.cursorPos = selection.first;
                            if (p.textChangedCallback)
                            {
                                p.textChangedCallback(p.text);
                            }
                            _textUpdate();
                        }
                    }
                }
                break;
            case Key::Left:
                event.accept = true;
                if (p.cursorPos > 0)
                {
                    if (event.modifiers & static_cast<int>(KeyModifier::Shift))
                    {
                        p.selection.select(p.cursorPos, p.cursorPos - 1);
                    }
                    else
                    {
                        p.selection.clear();
                    }

                    p.cursorPos--;
                    p.cursorVisible = true;
                    p.cursorTimer = std::chrono::steady_clock::now();

                    _setDrawUpdate();
                }
                break;
            case Key::Right:
                event.accept = true;
                if (p.cursorPos < p.text.size())
                {
                    if (event.modifiers & static_cast<int>(KeyModifier::Shift))
                    {
                        p.selection.select(p.cursorPos, p.cursorPos + 1);
                    }
                    else
                    {
                        p.selection.clear();
                    }

                    p.cursorPos++;
                    p.cursorVisible = true;
                    p.cursorTimer = std::chrono::steady_clock::now();

                    _setDrawUpdate();
                }
                break;
            case Key::Home:
                event.accept = true;
                if (p.cursorPos > 0)
                {
                    if (event.modifiers & static_cast<int>(KeyModifier::Shift))
                    {
                        p.selection.select(p.cursorPos, 0);
                    }
                    else
                    {
                        p.selection.clear();
                    }

                    p.cursorPos = 0;
                    p.cursorVisible = true;
                    p.cursorTimer = std::chrono::steady_clock::now();

                    _setDrawUpdate();
                }
                break;
            case Key::End:
                event.accept = true;
                if (p.cursorPos < p.text.size())
                {
                    if (event.modifiers & static_cast<int>(KeyModifier::Shift))
                    {
                        p.selection.select(p.cursorPos, p.text.size());
                    }
                    else
                    {
                        p.selection.clear();
                    }

                    p.cursorPos = p.text.size();
                    p.cursorVisible = true;
                    p.cursorTimer = std::chrono::steady_clock::now();

                    _setDrawUpdate();
                }
                break;
            case Key::Backspace:
                event.accept = true;
                if (p.selection.isValid())
                {
                    const auto selection = p.selection.getSorted();
                    p.text.erase(
                        selection.first,
                        selection.second - selection.first);
                    p.selection.clear();
                    p.cursorPos = selection.first;
                    if (p.textChangedCallback)
                    {
                        p.textChangedCallback(p.text);
                    }
                    _textUpdate();
                }
                else if (p.cursorPos > 0)
                {
                    const auto i = p.text.begin() + p.cursorPos - 1;
                    p.text.erase(i);
                    p.cursorPos--;
                    if (p.textChangedCallback)
                    {
                        p.textChangedCallback(p.text);
                    }
                    _textUpdate();
                }
                break;
            case Key::Delete:
                event.accept = true;
                if (p.selection.isValid())
                {
                    const auto selection = p.selection.getSorted();
                    p.text.erase(
                        selection.first,
                        selection.second - selection.first);
                    p.selection.clear();
                    p.cursorPos = selection.first;
                    if (p.textChangedCallback)
                    {
                        p.textChangedCallback(p.text);
                    }
                    _textUpdate();
                }
                else if (p.cursorPos < p.text.size())
                {
                    const auto i = p.text.begin() + p.cursorPos;
                    p.text.erase(i);
                    if (p.textChangedCallback)
                    {
                        p.textChangedCallback(p.text);
                    }
                    _textUpdate();
                }
                break;
            case Key::Return:
                event.accept = true;
                if (p.textCallback)
                {
                    p.textCallback(p.text);
                }
                break;
            case Key::Escape:
                event.accept = true;
                releaseKeyFocus();
                break;
            case Key::Up:
            case Key::Down:
            case Key::PageUp:
            case Key::PageDown:
            case Key::Tab:
                break;
            default:
                if (0 == event.modifiers || event.modifiers == static_cast<int>(KeyModifier::Shift))
                {
                    event.accept = true;
                }
                break;
            }
        }*/
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
        /*if (p.selection.isValid())
        {
            const auto selection = p.selection.getSorted();
            p.text.replace(
                selection.first,
                selection.second - selection.first,
                event.text);
            p.selection.clear();
            p.cursorPos = selection.first + event.text.size();
        }
        else
        {
            p.text.insert(p.cursorPos, event.text);
            p.cursorPos += event.text.size();
        }
        if (p.textChangedCallback)
        {
            p.textChangedCallback(p.text);
        }
        _textUpdate();*/
    }

    TextPos TextEditWidget::_getCursorPos(const V2I& value) const
    {
        return TextPos();
    }

    void TextEditWidget::_cursorReset()
    {
        FTK_P();
        p.cursorVisible = true;
        p.cursorTimer = std::chrono::steady_clock::now();
    }

    void TextEditWidget::_textUpdate()
    {
        FTK_P();
        p.size.displayScale.reset();
        _setSizeUpdate();
        _setDrawUpdate();
    }
}