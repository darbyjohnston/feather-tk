// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/UI/TextEditPrivate.h>

namespace ftk
{
    struct TextEditModel::Private
    {
        std::shared_ptr<ObservableList<std::string> > text;
        std::shared_ptr<ObservableValue<TextPos> > cursor;
        std::shared_ptr<ObservableValue<Selection> > selection;
    };

    void TextEditModel::_init()
    {
        FTK_P();
        p.text = ObservableList<std::string>::create();
        p.cursor = ObservableValue<TextPos>::create(TextPos(0, 0));
        p.selection = ObservableValue<Selection>::create();
    }

    TextEditModel::TextEditModel() :
        _p(new Private)
    {}

    TextEditModel::~TextEditModel()
    {}

    std::shared_ptr<TextEditModel> TextEditModel::create()
    {
        auto out = std::shared_ptr<TextEditModel>(new TextEditModel);
        out->_init();
        return out;
    }

    const std::vector<std::string>& TextEditModel::getText() const
    {
        return _p->text->get();
    }

    std::shared_ptr<IObservableList<std::string> > TextEditModel::observeText() const
    {
        return _p->text;
    }

    void TextEditModel::setText(const std::vector<std::string>& value)
    {
        if (_p->text->setIfChanged(value))
        {
            _p->cursor->setIfChanged(TextPos(0, 0));
        }
    }

    void TextEditModel::clearText()
    {
        setText({});
    }

    const TextPos& TextEditModel::getCursor() const
    {
        return _p->cursor->get();
    }

    std::shared_ptr<IObservableValue<TextPos> > TextEditModel::observeCursor() const
    {
        return _p->cursor;
    }

    void TextEditModel::setCursor(const TextPos& value)
    {
        _p->cursor->setIfChanged(value);
    }

    void TextEditModel::moveCursor(MoveCursor value, bool select)
    {
        FTK_P();
        const auto& text = p.text->get();
        TextPos cursor = p.cursor->get();
        if (cursor.line >= 0 && cursor.line < static_cast<int>(text.size()))
        {
            switch (value)
            {
            case MoveCursor::Left:
                if (cursor.chr > 0)
                {
                    --cursor.chr;
                }
                break;
            case MoveCursor::Right:
                if (cursor.chr < static_cast<int>(text[cursor.line].size()))
                {
                    ++cursor.chr;
                }
                break;
            case MoveCursor::Up:
                if (cursor.line > 0)
                {
                    --cursor.line;
                    cursor.chr = std::min(cursor.chr, static_cast<int>(text[cursor.line].size()));
                }
                break;
            case MoveCursor::Down:
                if (cursor.line < static_cast<int>(text.size()) - 1)
                {
                    ++cursor.line;
                    cursor.chr = std::min(cursor.chr, static_cast<int>(text[cursor.line].size()));
                }
                break;
            case MoveCursor::Home:
                if (cursor.chr > 0)
                {
                    cursor.chr = 0;
                }
                break;
            case MoveCursor::End:
                if (cursor.chr < static_cast<int>(text[cursor.line].size()))
                {
                    cursor.chr = static_cast<int>(text[cursor.line].size());
                }
                break;
            default: break;
            }
            p.cursor->setIfChanged(cursor);
        }
    }

    const Selection& TextEditModel::getSelection() const
    {
        return _p->selection->get();
    }

    std::shared_ptr<IObservableValue<Selection> > TextEditModel::observeSelection() const
    {
        return _p->selection;
    }

    void TextEditModel::setSelection(const Selection& value)
    {
        _p->selection->setIfChanged(value);
    }

    void TextEditModel::selectAll()
    {
        FTK_P();
        SelectionPair select;
        const auto& text = p.text->get();
        if (!text.empty())
        {
            select.first.line = 0;
            select.first.chr = static_cast<int>(text.front().size()) - 1;
            select.second.line = static_cast<int>(text.size()) - 1;
            select.second.chr = static_cast<int>(text.back().size()) - 1;
        }
        auto selection = p.selection->get();
        if (select != selection.get())
        {
            selection.clear();
            selection.select(select);
            p.selection->setIfChanged(selection);
        }
    }

    void TextEditModel::selectNone()
    {
        FTK_P();
        auto selection = p.selection->get();
        if (selection.isValid())
        {
            selection.clear();
            p.selection->setIfChanged(selection);
        }
    }
}