// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/UI/TextEditPrivate.h>

#include <ftk/UI/ScrollWidget.h>

namespace ftk
{
    TextPos::TextPos(int line, int chr) :
        line(line),
        chr(chr)
    {}

    bool TextPos::operator == (const TextPos& other) const
    {
        return line == other.line && chr == other.chr;
    }

    bool TextPos::operator != (const TextPos& other) const
    {
        return !(*this == other);
    }

    bool TextPos::operator < (const TextPos& other) const
    {
        return line < other.line && chr < other.chr;
    }

    bool TextPos::operator <= (const TextPos& other) const
    {
        return line <= other.line && chr <= other.chr;
    }

    bool TextPos::operator > (const TextPos& other) const
    {
        return line > other.line && chr > other.chr;
    }

    bool TextPos::operator >= (const TextPos& other) const
    {
        return line >= other.line && chr >= other.chr;
    }

    const SelectionPair& Selection::get() const
    {
        return _pair;
    }

    SelectionPair Selection::getSorted() const
    {
        return std::make_pair(
            std::min(_pair.first, _pair.second),
            std::max(_pair.first, _pair.second));
    }

    bool Selection::isValid() const
    {
        return
            _pair.first != posInvalid &&
            _pair.second != posInvalid &&
            _pair.first != _pair.second;
    }

    void Selection::set(const SelectionPair& value)
    {
        _pair = value;
    }

    void Selection::setFirst(const TextPos& value)
    {
        _pair.first = value;
    }

    void Selection::setSecond(const TextPos& value)
    {
        _pair.second = value;
    }

    void Selection::select(const SelectionPair& value)
    {
        if (posInvalid == _pair.first)
        {
            _pair.first = value.first;
            _pair.second = value.second;
        }
        else
        {
            _pair.second = value.second;
        }
    }

    void Selection::select(const TextPos& first, const TextPos& second)
    {
        select(SelectionPair(first, second));
    }

    void Selection::clear()
    {
        _pair = std::make_pair(posInvalid, posInvalid);
    }

    bool Selection::operator == (const Selection& other) const
    {
        return _pair == other._pair;
    }

    bool Selection::operator != (const Selection& other) const
    {
        return !(*this == other);
    }

    struct TextEdit::Private
    {
        std::shared_ptr<TextEditModel> model;
        std::shared_ptr<TextEditWidget> widget;
        std::shared_ptr<ScrollWidget> scrollWidget;

        std::shared_ptr<ValueObserver<TextPos> > cursorObserver;
    };

    void TextEdit::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "ftk::TextEdit", parent);
        FTK_P();

        p.model = TextEditModel::create();

        p.widget = TextEditWidget::create(context, p.model);

        p.scrollWidget = ScrollWidget::create(context, ScrollType::Both, shared_from_this());
        p.scrollWidget->setWidget(p.widget);

        p.widget->setFocusCallback(
            [this](bool value)
            {
                _p->scrollWidget->setBorderColorRole(
                    value ? ColorRole::KeyFocus : ColorRole::Border);
            });

        p.cursorObserver = ValueObserver<TextPos>::create(
            p.model->observeCursor(),
            [this](const TextPos&)
            {
                _p->scrollWidget->scrollTo(_p->widget->getCursorBox(true));
            });
    }

    TextEdit::TextEdit() :
        _p(new Private)
    {}

    TextEdit::~TextEdit()
    {}

    std::shared_ptr<TextEdit> TextEdit::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<TextEdit>(new TextEdit);
        out->_init(context, parent);
        return out;
    }

    const std::vector<std::string>& TextEdit::getText() const
    {
        return _p->widget->getText();
    }

    void TextEdit::setText(const std::vector<std::string>& value)
    {
        _p->widget->setText(value);
    }

    void TextEdit::clearText()
    {
        _p->widget->clearText();
    }

    void TextEdit::setTextCallback(const std::function<void(const std::vector<std::string>&)>& value)
    {
        _p->widget->setTextCallback(value);
    }

    void TextEdit::selectAll()
    {
        _p->widget->selectAll();
    }

    void TextEdit::selectNone()
    {
        _p->widget->selectNone();
    }

    FontRole TextEdit::getFontRole() const
    {
        return _p->widget->getFontRole();
    }

    void TextEdit::setFontRole(FontRole value)
    {
        _p->widget->setFontRole(value);
    }

    void TextEdit::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _p->scrollWidget->setGeometry(value);
    }

    void TextEdit::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        _setSizeHint(_p->scrollWidget->getSizeHint());
    }
}