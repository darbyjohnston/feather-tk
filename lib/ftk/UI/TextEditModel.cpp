// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/UI/TextEditModel.h>

namespace ftk
{
    TextEditPos::TextEditPos(int line, int chr) :
        line(line),
        chr(chr)
    {}

    bool TextEditPos::operator == (const TextEditPos& other) const
    {
        return line == other.line && chr == other.chr;
    }

    bool TextEditPos::operator != (const TextEditPos& other) const
    {
        return !(*this == other);
    }

    bool TextEditPos::operator < (const TextEditPos& other) const
    {
        return line < other.line && chr < other.chr;
    }

    bool TextEditPos::operator <= (const TextEditPos& other) const
    {
        return line <= other.line && chr <= other.chr;
    }

    bool TextEditPos::operator > (const TextEditPos& other) const
    {
        return line > other.line && chr > other.chr;
    }

    bool TextEditPos::operator >= (const TextEditPos& other) const
    {
        return line >= other.line && chr >= other.chr;
    }

    const TextEditSelectionPair& TextEditSelection::get() const
    {
        return _pair;
    }

    TextEditSelectionPair TextEditSelection::getSorted() const
    {
        return std::make_pair(
            std::min(_pair.first, _pair.second),
            std::max(_pair.first, _pair.second));
    }

    bool TextEditSelection::isValid() const
    {
        return
            _pair.first != textEditPosInvalid &&
            _pair.second != textEditPosInvalid &&
            _pair.first != _pair.second;
    }

    void TextEditSelection::set(const TextEditSelectionPair& value)
    {
        _pair = value;
    }

    void TextEditSelection::setFirst(const TextEditPos& value)
    {
        _pair.first = value;
    }

    void TextEditSelection::setSecond(const TextEditPos& value)
    {
        _pair.second = value;
    }

    void TextEditSelection::select(const TextEditSelectionPair& value)
    {
        if (textEditPosInvalid == _pair.first)
        {
            _pair.first = value.first;
            _pair.second = value.second;
        }
        else
        {
            _pair.second = value.second;
        }
    }

    void TextEditSelection::select(const TextEditPos& first, const TextEditPos& second)
    {
        select(TextEditSelectionPair(first, second));
    }

    void TextEditSelection::clear()
    {
        _pair = std::make_pair(textEditPosInvalid, textEditPosInvalid);
    }

    bool TextEditSelection::operator == (const TextEditSelection& other) const
    {
        return _pair == other._pair;
    }

    bool TextEditSelection::operator != (const TextEditSelection& other) const
    {
        return !(*this == other);
    }

    struct TextEditModel::Private
    {
        std::shared_ptr<ObservableList<std::string> > text;
        std::shared_ptr<ObservableValue<TextEditPos> > cursor;
        std::shared_ptr<ObservableValue<TextEditSelection> > selection;
    };

    void TextEditModel::_init()
    {
        FTK_P();
        p.text = ObservableList<std::string>::create();
        p.cursor = ObservableValue<TextEditPos>::create(TextEditPos(0, 0));
        p.selection = ObservableValue<TextEditSelection>::create();
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
            _p->cursor->setIfChanged(TextEditPos(0, 0));
        }
    }

    void TextEditModel::clearText()
    {
        setText({});
    }

    const TextEditPos& TextEditModel::getCursor() const
    {
        return _p->cursor->get();
    }

    std::shared_ptr<IObservableValue<TextEditPos> > TextEditModel::observeCursor() const
    {
        return _p->cursor;
    }

    void TextEditModel::setCursor(const TextEditPos& value)
    {
        _p->cursor->setIfChanged(value);
    }

    const TextEditSelection& TextEditModel::getSelection() const
    {
        return _p->selection->get();
    }

    std::shared_ptr<IObservableValue<TextEditSelection> > TextEditModel::observeSelection() const
    {
        return _p->selection;
    }

    void TextEditModel::setSelection(const TextEditSelection& value)
    {
        _p->selection->setIfChanged(value);
    }

    void TextEditModel::selectAll()
    {
        FTK_P();
        TextEditSelectionPair select;
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

    void TextEditModel::clearSelection()
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
        TextEditPos cursor = p.cursor->get();
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
        TextEditPos cursor = p.cursor->get();
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
        case Key::Delete:
            if (cursor.line >= 0 && cursor.line < static_cast<int>(text.size()))
            {
                std::string line = text[cursor.line];
                if (cursor.chr < line.size())
                {
                    line.erase(cursor.chr, 1);
                    p.text->setItem(cursor.line, line);
                }
                else if (cursor.line < static_cast<int>(text.size()) - 1)
                {
                    line = text[cursor.line + 1];
                    p.text->removeItem(cursor.line + 1);
                    p.text->setItem(cursor.line, text[cursor.line] + line);
                }
            }
            out = true;
            break;
        case Key::Return:
        case Key::KeypadEnter:
            if (cursor.line >= 0 && cursor.line < static_cast<int>(text.size()))
            {
                std::string line = text[cursor.line];
                if (0 == cursor.chr)
                {
                    p.text->insertItem(cursor.line, std::string());
                    ++cursor.line;
                }
                else if (cursor.chr < static_cast<int>(line.size()) - 1)
                {
                    p.text->insertItem(cursor.line + 1, line.substr(cursor.chr));
                    p.text->setItem(cursor.line, line.erase(cursor.chr));
                    ++cursor.line;
                    cursor.chr = 0;
                }
                else
                {
                    p.text->insertItem(cursor.line + 1, std::string());
                    ++cursor.line;
                    cursor.chr = 0;
                }
            }
            out = true;
            break;
        default: break;
        }
        p.cursor->setIfChanged(cursor);
        return out;
    }
}
