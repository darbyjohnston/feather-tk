// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/UI/TextEditModel.h>

#include <ftk/UI/ClipboardSystem.h>

#include <ftk/Core/String.h>

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

    bool TextEditModelOptions::operator != (const TextEditModelOptions& other) const
    {
        return !(*this == other);
    }

    bool TextEditModelOptions::operator == (const TextEditModelOptions& other) const
    {
        return tabSpaceCount == other.tabSpaceCount;
    }

    bool TextEditSelection::operator != (const TextEditSelection& other) const
    {
        return !(*this == other);
    }

    struct TextEditModel::Private
    {
        std::weak_ptr<Context> context;
        std::shared_ptr<ObservableList<std::string> > text;
        std::shared_ptr<ObservableValue<TextEditPos> > cursor;
        std::shared_ptr<ObservableValue<TextEditSelection> > selection;
        int pageRows = 0;
        TextEditModelOptions options;
    };

    void TextEditModel::_init(const std::shared_ptr<Context>& context)
    {
        FTK_P();
        p.context = context;
        p.text = ObservableList<std::string>::create();
        p.cursor = ObservableValue<TextEditPos>::create(TextEditPos(0, 0));
        p.selection = ObservableValue<TextEditSelection>::create();
    }

    TextEditModel::TextEditModel() :
        _p(new Private)
    {}

    TextEditModel::~TextEditModel()
    {}

    std::shared_ptr<TextEditModel> TextEditModel::create(const std::shared_ptr<Context>& context)
    {
        auto out = std::shared_ptr<TextEditModel>(new TextEditModel);
        out->_init(context);
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
        _p->selection->setIfChanged(_getSelectAll());
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
                // Move the cursor left.
                --cursor.chr;
            }
            else if (
                cursor.line > 0 &&
                cursor.line < static_cast<int>(text.size()))
            {
                // Move the cursor up a line.
                --cursor.line;
                cursor.chr = static_cast<int>(text[cursor.line].size());
            }
            out = true;
            break;

        case Key::Right:
            if (cursor.line >= 0 &&
                cursor.line < static_cast<int>(text.size()) &&
                cursor.chr < static_cast<int>(text[cursor.line].size()))
            {
                // Move the cursor right.
                ++cursor.chr;
            }
            else if (
                cursor.line >= 0 &&
                cursor.line < static_cast<int>(text.size()))
            {
                // Move the cursor down a line.
                ++cursor.line;
                cursor.chr = 0;
            }
            out = true;
            break;

        case Key::Up:
            if (cursor.line > 0 &&
                cursor.line < static_cast<int>(text.size()))
            {
                // Move the cursor up a line.
                --cursor.line;
                cursor.chr = std::min(cursor.chr, static_cast<int>(text[cursor.line].size()));
            }
            out = true;
            break;

        case Key::Down:
            if (cursor.line >= 0 &&
                cursor.line < static_cast<int>(text.size()) - 1)
            {
                // Move the cursor down a line.
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
                // Move the cursor to the beginning of the line.
                cursor.chr = 0;
            }
            out = true;
            break;

        case Key::End:
            if (cursor.line >= 0 &&
                cursor.line < static_cast<int>(text.size()) &&
                cursor.chr < static_cast<int>(text[cursor.line].size()))
            {
                // Move the cursor to the end of the line.
                cursor.chr = static_cast<int>(text[cursor.line].size());
            }
            out = true;
            break;

        case Key::PageUp:
            if (cursor.line >= 0 &&
                cursor.line < static_cast<int>(text.size()))
            {
                // Move the cursor up a page.
                cursor.line = std::max(0, cursor.line - p.pageRows);
            }
            out = true;
            break;

        case Key::PageDown:
            if (cursor.line >= 0 &&
                cursor.line < static_cast<int>(text.size()))
            {
                // Move the cursor down a page.
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
            else if (
                cursor.line >= 0 &&
                cursor.line < static_cast<int>(text.size()))
            {
                std::string line = text[cursor.line];
                if (cursor.chr > 0)
                {
                    // Remove the previous character.
                    --cursor.chr;
                    line.erase(cursor.chr, 1);
                    p.text->setItem(cursor.line, line);
                }
                else if (cursor.line > 0)
                {
                    // Append this line to the previous line.
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
            else if (
                cursor.line >= 0 &&
                cursor.line < static_cast<int>(text.size()))
            {
                std::string line = text[cursor.line];
                if (cursor.chr < line.size())
                {
                    // Delete the current character.
                    line.erase(cursor.chr, 1);
                    p.text->setItem(cursor.line, line);
                }
                else if (cursor.line < static_cast<int>(text.size()) - 1)
                {
                    // Append the previous line to this line.
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
            if (cursor.line >= 0 &&
                cursor.line < static_cast<int>(text.size()))
            {
                std::string line = text[cursor.line];
                if (0 == cursor.chr)
                {
                    // Insert a line.
                    p.text->insertItem(cursor.line, std::string());
                    ++cursor.line;
                }
                else if (cursor.chr < static_cast<int>(line.size()))
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

        case Key::A:
            if (static_cast<int>(KeyModifier::Control) == modifiers)
            {
                // Select all.
                selection = _getSelectAll();
                out = true;
            }
            break;

        case Key::C:
            if (static_cast<int>(KeyModifier::Control) == modifiers)
            {
                if (selection.isValid())
                {
                    // Copy.
                    if (auto context = p.context.lock())
                    {
                        auto clipboard = context->getSystem<ClipboardSystem>();
                        const auto lines = _getSelection(selection);
                        clipboard->setText(join(lines, '\n'));
                    }
                }
                out = true;
            }
            break;

        case Key::X:
            if (static_cast<int>(KeyModifier::Control) == modifiers)
            {
                if (selection.isValid())
                {
                    // Cut.
                    if (auto context = p.context.lock())
                    {
                        auto clipboard = context->getSystem<ClipboardSystem>();
                        const auto lines = _getSelection(selection);
                        clipboard->setText(join(lines, '\n'));
                        _replace(std::string(), cursor, selection);
                    }
                }
                out = true;
            }
            break;

        case Key::V:
            if (static_cast<int>(KeyModifier::Control) == modifiers)
            {
                // Paste.
                if (auto context = p.context.lock())
                {
                    auto clipboard = context->getSystem<ClipboardSystem>();
                    auto lines = splitLines(clipboard->getText());
                    if (selection.isValid())
                    {
                        _replace(std::string(), cursor, selection);
                    }
                    if (lines.size() > 0 &&
                        cursor.line >= 0 &&
                        cursor.line < static_cast<int>(text.size()))
                    {
                        const std::string& line = text[cursor.line];
                        const int chr = cursor.chr;
                        cursor.chr = lines.back().size();
                        lines.front().insert(0, line.substr(0, chr));
                        lines.back().append(line.substr(chr));
                        p.text->replaceItems(cursor.line, cursor.line, lines);
                        cursor.line += lines.size() - 1;
                    }
                    else
                    {
                        p.text->pushBack(lines);
                    }
                }
                out = true;
            }
            break;

        case Key::Tab:
            if (0 == modifiers &&
                selection.isValid() &&
                selection.first.line >= 0 &&
                selection.first.line < static_cast<int>(text.size()) &&
                selection.second.line >= 0 &&
                selection.second.line < static_cast<int>(text.size()))
            {
                // Indent.
                std::vector<std::string> lines;
                const TextEditPos min = selection.min();
                const TextEditPos max = selection.max();
                for (int i = min.line; i <= max.line; ++i)
                {
                    lines.push_back(std::string(p.options.tabSpaceCount, ' ') + text[i]);
                }
                p.text->replaceItems(min.line, max.line, lines);
                cursor.chr += p.options.tabSpaceCount;
                selection.first.chr += p.options.tabSpaceCount;
                selection.second.chr += p.options.tabSpaceCount;
            }
            else if (
                static_cast<int>(KeyModifier::Shift) == modifiers &&
                selection.isValid() &&
                selection.first.line >= 0 &&
                selection.first.line < static_cast<int>(text.size()) &&
                selection.second.line >= 0 &&
                selection.second.line < static_cast<int>(text.size()))
            {
                // Un-indent.
                std::vector<std::string> lines;
                const TextEditPos min = selection.min();
                const TextEditPos max = selection.max();
                for (int i = min.line; i <= max.line; ++i)
                {
                    std::string line = text[i];
                    int j = 0;
                    for (;
                        j < p.options.tabSpaceCount &&
                        j < line.size() &&
                        ' ' == line[0];
                        ++j)
                        ;
                    if (j > 0)
                    {
                        line.erase(0, j);
                    }
                    lines.push_back(line);
                }
                p.text->replaceItems(min.line, max.line, lines);
                cursor.chr = std::max(0, cursor.chr - p.options.tabSpaceCount);
                selection.first.chr = std::max(0, selection.first.chr - p.options.tabSpaceCount);
                selection.second.chr = std::max(0, selection.second.chr - p.options.tabSpaceCount);
            }
            else if (
                cursor.line >= 0 &&
                cursor.line < static_cast<int>(text.size()) &&
                cursor.chr >= 0 &&
                cursor.chr <= text[cursor.line].size())
            {
                // Insert spaces.
                std::string line = text[cursor.line];
                line.insert(cursor.chr, std::string(p.options.tabSpaceCount, ' '));
                cursor.chr += p.options.tabSpaceCount;
                p.text->setItem(cursor.line, line);
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
        else if (
            min.line >= 0 && min.line < static_cast<int>(text.size()) &&
            max.line >= 0 && max.line < static_cast<int>(text.size()))
        {
            const std::string line =
                text[min.line].substr(0, min.chr) +
                value +
                text[max.line].substr(max.chr);
            if (!line.empty())
            {
                p.text->replaceItems(min.line, max.line, { line });
            }
            else
            {
                p.text->removeItems(min.line, max.line);
            }
            cursor.line = min.line;
            cursor.chr = min.chr;
            selection = TextEditSelection();
        }
    }

    TextEditSelection TextEditModel::_getSelectAll() const
    {
        FTK_P();
        TextEditSelection out;
        const auto& text = p.text->get();
        if (!text.empty())
        {
            out = TextEditSelection(
                TextEditPos(0, 0),
                TextEditPos(
                    static_cast<int>(text.size()) - 1,
                    static_cast<int>(text.back().size())));
        }
        return out;
    }

    std::vector<std::string> TextEditModel::_getSelection(const TextEditSelection& selection) const
    {
        FTK_P();
        std::vector<std::string> out;
        const auto& text = p.text->get();
        const TextEditPos min = selection.min();
        const TextEditPos max = selection.max();
        if (min.line == max.line)
        {
            out.push_back(text[min.line].substr(min.chr, max.chr));
        }
        else
        {
            out.push_back(text[min.line].substr(min.chr));
            for (int i = min.line + 1; i < max.line; ++i)
            {
                out.push_back(text[i]);
            }
            out.push_back(text[max.line].substr(0, max.chr));
        }
        return out;
    }
}
