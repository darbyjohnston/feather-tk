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
        return line < other.line ||
            (line == other.line && chr < other.chr);
    }

    bool TextEditPos::operator > (const TextEditPos& other) const
    {
        return line > other.line ||
            (line == other.line) && chr > other.chr;
    }

    TextEditSelection::TextEditSelection(const TextEditPos& first) :
        first(first)
    {}

    TextEditSelection::TextEditSelection(const TextEditPos& first, const TextEditPos& second) :
        first(first),
        second(second)
    {}

    bool TextEditSelection::isValid() const
    {
        return
            first != textEditPosInvalid &&
            second != textEditPosInvalid &&
            first != second;
    }

    TextEditPos TextEditSelection::min() const
    {
        return std::min(first, second);
    }

    TextEditPos TextEditSelection::max() const
    {
        return std::max(first, second);
    }

    bool TextEditSelection::operator == (const TextEditSelection& other) const
    {
        return
            first == other.first &&
            second == other.second;
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
        int pageRows = 0;
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
        TextEditSelection selection;
        const auto& text = p.text->get();
        if (!text.empty())
        {
            selection.first.line = 0;
            selection.first.chr = static_cast<int>(text.front().size()) - 1;
            selection.second.line = static_cast<int>(text.size()) - 1;
            selection.second.chr = static_cast<int>(text.back().size()) - 1;
        }
        p.selection->setIfChanged(selection);
    }

    void TextEditModel::clearSelection()
    {
        FTK_P();
        p.selection->setIfChanged(TextEditSelection());
    }

    void TextEditModel::text(const std::string& value)
    {
        FTK_P();
        const auto& text = p.text->get();
        TextEditPos cursor = p.cursor->get();
        TextEditSelection selection = p.selection->get();

        if (selection.isValid())
        {
            // Replace the selection.
            _replace(value, cursor, selection);
            cursor.chr += value.size();
        }
        else
        {
            if (cursor.line >= 0 && cursor.line < static_cast<int>(text.size()))
            {
                // Insert text at the cursor.
                std::string line = text[cursor.line];
                line.insert(cursor.chr, value);
                cursor.chr += value.size();
                p.text->setItem(cursor.line, line);
            }
            else
            {
                // Add a line.
                std::string line = value;
                cursor.chr = line.size();
                p.text->pushBack(line);
            }
        }

        p.cursor->setIfChanged(cursor);
        p.selection->setIfChanged(selection);
    }

    bool TextEditModel::key(Key key, int modifiers)
    {
        FTK_P();
        bool out = false;
        const auto& text = p.text->get();
        TextEditPos cursor = p.cursor->get();
        TextEditSelection selection = p.selection->get();

        // Start selection.
        switch (key)
        {
        case Key::Left:
        case Key::Right:
        case Key::Up:
        case Key::Down:
        case Key::Home:
        case Key::End:
        case Key::PageUp:
        case Key::PageDown:
            if (static_cast<int>(KeyModifier::Shift) == modifiers)
            {
                if (!selection.isValid())
                {
                    selection = TextEditSelection(cursor);
                }
            }
            else
            {
                selection = TextEditSelection();
            }
            break;
        default: break;
        }

        // Handle keys.
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
        case Key::PageUp:
            if (cursor.line >= 0 &&
                cursor.line < static_cast<int>(text.size()))
            {
                cursor.line = std::max(0, cursor.line - p.pageRows);
            }
            out = true;
            break;
        case Key::PageDown:
            if (cursor.line >= 0 &&
                cursor.line < static_cast<int>(text.size()))
            {
                cursor.line = std::min(cursor.line + p.pageRows, static_cast<int>(text.size()) - 1);
            }
            out = true;
            break;
        case Key::Backspace:
            if (selection.isValid())
            {
                // Remove the selection.
                _replace(std::string(), cursor, selection);
            }
            else if (cursor.line >= 0 && cursor.line < static_cast<int>(text.size()))
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
            if (selection.isValid())
            {
                // Remove the selection.
                _replace(std::string(), cursor, selection);
            }
            else if (cursor.line >= 0 && cursor.line < static_cast<int>(text.size()))
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
            if (selection.isValid())
            {
                // Remove the selection.
                _replace(std::string(), cursor, selection);
            }
            if (cursor.line >= 0 && cursor.line < static_cast<int>(text.size()))
            {
                std::string line = text[cursor.line];
                if (0 == cursor.chr)
                {
                    // Insert a line.
                    p.text->insertItem(cursor.line, std::string());
                    ++cursor.line;
                }
                else if (cursor.chr < static_cast<int>(line.size()) - 1)
                {
                    // Break the line.
                    p.text->insertItem(cursor.line + 1, line.substr(cursor.chr));
                    p.text->setItem(cursor.line, line.erase(cursor.chr));
                    ++cursor.line;
                    cursor.chr = 0;
                }
                else
                {
                    // Append a line.
                    p.text->insertItem(cursor.line + 1, std::string());
                    ++cursor.line;
                    cursor.chr = 0;
                }
            }
            else
            {
                // Add a line.
                p.text->pushBack(std::string());
                ++cursor.line;
                cursor.chr = 0;
            }
            out = true;
            break;
        default: break;
        }

        // Finish selection.
        switch (key)
        {
        case Key::Left:
        case Key::Right:
        case Key::Up:
        case Key::Down:
        case Key::Home:
        case Key::End:
        case Key::PageUp:
        case Key::PageDown:
            if (static_cast<int>(KeyModifier::Shift) == modifiers)
            {
                selection.second = cursor;
            }
            break;
        default: break;
        }

        p.cursor->setIfChanged(cursor);
        p.selection->setIfChanged(selection);
        return out;
    }

    void TextEditModel::setPageRows(int value)
    {
        _p->pageRows = value;
    }

    void TextEditModel::_replace(
        const std::string& value,
        TextEditPos& cursor,
        TextEditSelection& selection)
    {
        FTK_P();
        const TextEditPos min = selection.min();
        const TextEditPos max = selection.max();
        const auto& text = p.text->get();
        if (min.line == max.line &&
            min.line >= 0 && min.line < static_cast<int>(text.size()))
        {
            std::string line = text[min.line];
            line.replace(min.chr, max.chr - min.chr, value);
            p.text->setItem(min.line, line);
            cursor.line = min.line;
            cursor.chr = min.chr;
            selection = TextEditSelection();
        }
    }
}
