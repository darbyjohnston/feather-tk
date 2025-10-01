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

    void TextEditModel::text(const std::string& value)
    {
        FTK_P();
        const auto& text = p.text->get();
        TextPos cursor = p.cursor->get();
        if (cursor.line >= 0 && cursor.line < text.size())
        {
            std::string line = text[cursor.line];
            line.insert(cursor.chr, value);
            cursor.chr += value.size();
            p.text->setItem(cursor.line, line);
        }
        else
        {
            std::string line = value;
            cursor.chr = line.size();
            p.text->pushBack(line);
        }
        p.cursor->setIfChanged(cursor);
    }

    bool TextEditModel::key(Key key, int modifiers)
    {
        FTK_P();
        bool out = false;
        const auto& text = p.text->get();
        TextPos cursor = p.cursor->get();
        switch (key)
        {
        case Key::Left:
            if (cursor.line >= 0 &&
                cursor.line < static_cast<int>(text.size()) &&
                cursor.chr > 0)
            {
                --cursor.chr;
            }
            out = true;
            break;
        case Key::Right:
            if (cursor.line >= 0 &&
                cursor.line < static_cast<int>(text.size()) &&
                cursor.chr < static_cast<int>(text[cursor.line].size()))
            {
                ++cursor.chr;
            }
            out = true;
            break;
        case Key::Up:
            if (cursor.line > 0 &&
                cursor.line < static_cast<int>(text.size()))
            {
                --cursor.line;
                cursor.chr = std::min(cursor.chr, static_cast<int>(text[cursor.line].size()));
            }
            out = true;
            break;
        case Key::Down:
            if (cursor.line >= 0 &&
                cursor.line < static_cast<int>(text.size()) - 1)
            {
                ++cursor.line;
                cursor.chr = std::min(cursor.chr, static_cast<int>(text[cursor.line].size()));
            }
            out = true;
            break;
        case Key::Home:
            if (cursor.line >= 0 &&
                cursor.line < static_cast<int>(text.size()) &&
                cursor.chr > 0)
            {
                cursor.chr = 0;
            }
            out = true;
            break;
        case Key::End:
            if (cursor.line >= 0 &&
                cursor.line < static_cast<int>(text.size()) &&
                cursor.chr < static_cast<int>(text[cursor.line].size()))
            {
                cursor.chr = static_cast<int>(text[cursor.line].size());
            }
            out = true;
            break;
        case Key::Backspace:
            if (cursor.line >= 0 && cursor.line < static_cast<int>(text.size()))
            {
                std::string line = text[cursor.line];
                if (cursor.chr > 0)
                {
                    --cursor.chr;
                    line.erase(cursor.chr, 1);
                    p.text->setItem(cursor.line, line);
                }
                else if (cursor.line > 0)
                {
                    p.text->removeItem(cursor.line);
                    --cursor.line;
                    cursor.chr = text[cursor.line].size();
                    p.text->setItem(cursor.line, text[cursor.line] + line);
                }
            }
            out = true;
            break;
        case Key::Return:
            if (cursor.line >= 0 && cursor.line < static_cast<int>(text.size()))
            {
                p.text->insertItem(cursor.line, std::string());
                ++cursor.line;
            }
            out = true;
            break;
        default: break;
        }
        p.cursor->setIfChanged(cursor);
        return out;
    }
}
