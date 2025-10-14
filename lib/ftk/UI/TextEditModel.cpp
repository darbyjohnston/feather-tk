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
        p.text = ObservableList<std::string>::create(textEditClear);
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
        FTK_P();
        if (p.text->setIfChanged(!value.empty() ? value : textEditClear))
        {
            p.cursor->setIfChanged(TextEditPos(0, 0));
            p.selection->setIfChanged(TextEditSelection());
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
        FTK_P();
        const auto& text = p.text->get();
        TextEditPos tmp = value;
        tmp.line = clamp(tmp.line, 0, static_cast<int>(text.size()) - 1);
        tmp.chr = tmp.line < text.size() ?
            clamp(tmp.chr, 0, static_cast<int>(text[tmp.line].size())) :
            0;
        if (p.cursor->setIfChanged(tmp))
        {
            p.selection->setIfChanged(TextEditSelection());
        }
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
        FTK_P();
        TextEditSelection tmp = value;
        if (tmp.isValid())
        {
            const auto& text = p.text->get();
            tmp.first.line = clamp(tmp.first.line, 0, static_cast<int>(text.size()) - 1);
            tmp.first.chr =  tmp.first.line < text.size() ?
                clamp(tmp.first.chr, 0, static_cast<int>(text[tmp.first.line].size())) :
                0;
            tmp.second.line = clamp(tmp.second.line, 0, static_cast<int>(text.size()) - 1);
            tmp.second.chr = tmp.second.line < text.size() ?
                clamp(tmp.second.chr, 0, static_cast<int>(text[tmp.second.line].size())) :
                0;
        }
        _p->selection->setIfChanged(tmp);
        _p->cursor->setIfChanged(tmp.second);
    }

    void TextEditModel::selectAll()
    {
        FTK_P();
        const TextEditSelection selection = _getSelectAll();
        p.selection->setIfChanged(selection);
        p.cursor->setIfChanged(selection.second);
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
            _replace(selection, { value });
            cursor.chr += value.size();
            selection = TextEditSelection();
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
            // Move the cursor left.
            cursor = _getPrev(cursor);
            out = true;
            break;

        case Key::Right:
            // Move the cursor right.
            cursor = _getNext(cursor);
            out = true;
            break;

        case Key::Up:
            if (cursor.line > 0)
            {
                // Move the cursor up a line.
                --cursor.line;
                cursor.chr = std::min(cursor.chr, static_cast<int>(text[cursor.line].size()));
            }
            out = true;
            break;

        case Key::Down:
            if (cursor.line < static_cast<int>(text.size() - 1))
            {
                // Move the cursor down a line.
                ++cursor.line;
                cursor.chr = cursor.line < static_cast<int>(text.size()) ?
                    std::min(cursor.chr, static_cast<int>(text[cursor.line].size())) :
                    0;
            }
            out = true;
            break;

        case Key::Home:
            if (cursor.chr > 0)
            {
                // Move the cursor to the beginning of the line.
                cursor.chr = 0;
            }
            out = true;
            break;

        case Key::End:
            if (cursor.line < static_cast<int>(text.size()) &&
                cursor.chr < static_cast<int>(text[cursor.line].size()))
            {
                // Move the cursor to the end of the line.
                cursor.chr = static_cast<int>(text[cursor.line].size());
            }
            out = true;
            break;

        case Key::PageUp:
            if (cursor.line > 0)
            {
                // Move the cursor up a page.
                cursor.line = std::max(0, cursor.line - p.pageRows);
                cursor.chr = std::min(cursor.chr, static_cast<int>(text[cursor.line].size()));
            }
            out = true;
            break;

        case Key::PageDown:
            if (cursor.line < static_cast<int>(text.size()))
            {
                // Move the cursor down a page.
                cursor.line += p.pageRows;
                if (cursor.line < static_cast<int>(text.size()))
                {
                    cursor.chr = std::min(cursor.chr, static_cast<int>(text[cursor.line].size()));
                }
                else
                {
                    cursor.line = static_cast<int>(text.size()) - 1;
                    cursor.chr = static_cast<int>(text[cursor.line].size());
                }
            }
            out = true;
            break;

        case Key::Backspace:
            if (selection.isValid())
            {
                // Remove the selection.
                _replace(selection, {});
                cursor = selection.min();
                selection = TextEditSelection();
            }
            else
            {
                const TextEditPos prev = _getPrev(cursor);
                if (cursor != prev)
                {
                    _replace(TextEditSelection(cursor, prev), {});
                    cursor = prev;
                }
            }
            out = true;
            break;

        case Key::Delete:
            if (selection.isValid())
            {
                // Remove the selection.
                _replace(selection, {});
                cursor = selection.min();
                selection = TextEditSelection();
            }
            else
            {
                const TextEditPos next = _getNext(cursor);
                if (cursor != next)
                {
                    _replace(TextEditSelection(cursor, next), {});
                }
            }
            out = true;
            break;

        case Key::Return:
        case Key::KeypadEnter:
            if (selection.isValid())
            {
                // Remove the selection.
                _replace(selection, {});
                cursor = selection.second;
                selection = TextEditSelection();
            }
            else if (0 == cursor.chr)
            {
                // Insert a line.
                p.text->insertItem(cursor.line, std::string());
                ++cursor.line;
            }
            else
            {
                // Break the line.
                const std::string& line = text[cursor.line];
                p.text->replaceItems(
                    cursor.line,
                    cursor.line + 1,
                    { line.substr(0, cursor.chr), line.substr(cursor.chr) });
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
                if (auto context = p.context.lock())
                {
                    // Copy.
                    auto clipboard = context->getSystem<ClipboardSystem>();
                    std::string text;
                    if (selection.isValid())
                    {
                        const auto lines = _getSelection(selection);
                        text = join(lines, '\n');
                    }
                    clipboard->setText(text);
                }
                out = true;
            }
            break;

        case Key::X:
            if (static_cast<int>(KeyModifier::Control) == modifiers)
            {
                if (auto context = p.context.lock())
                {
                    // Cut.
                    auto clipboard = context->getSystem<ClipboardSystem>();
                    std::string text;
                    if (selection.isValid())
                    {
                        const auto lines = _getSelection(selection);
                        text = join(lines, '\n');
                        _replace(selection, {});
                        cursor = selection.min();
                        selection = TextEditSelection();
                    }
                    clipboard->setText(text);
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
                    const std::string clipboardText = clipboard->getText();
                    if (!clipboardText.empty())
                    {
                        const auto lines = splitLines(clipboardText);
                        if (selection.isValid())
                        {
                            _replace(selection, lines);
                            cursor = selection.min();
                            selection = TextEditSelection();
                        }
                        else
                        {
                            _replace(TextEditSelection(cursor, cursor), lines);
                        }
                        if (1 == lines.size())
                        {
                            cursor.chr += static_cast<int>(lines.front().size());
                        }
                        else
                        {
                            cursor.line += static_cast<int>(lines.size()) - 1;
                            cursor.chr = static_cast<int>(lines.back().size());
                        }
                    }
                }
                out = true;
            }
            break;

        case Key::Tab:
            if (0 == modifiers &&
                selection.isValid())
            {
                // Indent.
                const TextEditPos min = selection.min();
                const TextEditPos max = selection.max();
                TextEditSelection tmp(min, max);
                tmp.first.chr = 0;
                tmp.second.chr = max.line < text.size() ? text[max.line].size() : 0;
                std::vector<std::string> lines = _getSelection(tmp);
                const std::string indent(p.options.tabSpaceCount, ' ');
                for (auto& line : lines)
                {
                    line.insert(0, indent);
                }
                _replace(tmp, lines);
                cursor.chr += p.options.tabSpaceCount;
                selection.first.chr += p.options.tabSpaceCount;
                selection.second.chr += p.options.tabSpaceCount;
            }
            else if (
                static_cast<int>(KeyModifier::Shift) == modifiers &&
                selection.isValid())
            {
                // Un-indent.
                const TextEditPos min = selection.min();
                const TextEditPos max = selection.max();
                TextEditSelection tmp(min, max);
                tmp.first.chr = 0;
                tmp.second.chr = max.line < text.size() ? text[max.line].size() : 0;
                std::vector<std::string> lines = _getSelection(tmp);
                int lastSpacesRemoved = 0;
                for (auto& line : lines)
                {
                    int j = 0;
                    for (;
                        j < p.options.tabSpaceCount &&
                        j < line.size() &&
                        ' ' == line[j];
                        ++j)
                        ;
                    if (j > 0)
                    {
                        line.erase(0, j);
                    }
                    lastSpacesRemoved = j;
                }
                _replace(tmp, lines);
                cursor.chr = std::max(0, cursor.chr - lastSpacesRemoved);
                selection.first.chr = std::max(0, selection.first.chr - lastSpacesRemoved);
                selection.second.chr = std::max(0, selection.second.chr - lastSpacesRemoved);
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

        // End selection.
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

    TextEditPos TextEditModel::_getNext(const TextEditPos& value) const
    {
        FTK_P();
        TextEditPos out = value;
        const auto& text = p.text->get();
        if (out.line >= 0 &&
            out.line < static_cast<int>(text.size()))
        {
            if (out.chr < static_cast<int>(text[out.line].size()))
            {
                ++out.chr;
            }
            else if (out.line < static_cast<int>(text.size()) - 1)
            {
                out.chr = 0;
                ++out.line;
            }
        }
        return out;
    }

    TextEditPos TextEditModel::_getPrev(const TextEditPos& value) const
    {
        FTK_P();
        TextEditPos out = value;
        const auto& text = p.text->get();
        if (out.line >= 0 &&
            out.line < static_cast<int>(text.size()))
        {
            if (out.chr > 0)
            {
                --out.chr;
            }
            else if (out.line > 0)
            {
                --out.line;
                out.chr = text[out.line].size();
            }
        }
        return out;
    }

    TextEditSelection TextEditModel::_getSelectAll() const
    {
        FTK_P();
        const auto& text = p.text->get();
        return !text.empty() ?
            TextEditSelection(
                TextEditPos(0, 0),
                TextEditPos(
                    static_cast<int>(text.size()) - 1,
                    static_cast<int>(text.back().size()))) :
            TextEditSelection();
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
            out.push_back(text[min.line].substr(min.chr, max.chr - min.chr));
        }
        else
        {
            out.push_back(text[min.line].substr(min.chr));
            for (int i = min.line + 1; i < max.line; ++i)
            {
                out.push_back(text[i]);
            }
            if (max.line < text.size())
            {
                out.push_back(text[max.line].substr(0, max.chr));
            }
        }
        return out;
    }

    void TextEditModel::_replace(
        const TextEditSelection& selection,
        const std::vector<std::string>& value)
    {
        FTK_P();
        const TextEditPos min = selection.min();
        const TextEditPos max = selection.max();
        const auto& text = p.text->get();
        if (selection == _getSelectAll())
        {
            p.text->setIfChanged(!value.empty() ? value : textEditClear);
        }
        else if (min.line == max.line && value.size() <= 1)
        {
            const std::string& line = text[min.line];
            const std::string tmp =
                line.substr(0, min.chr) +
                (!value.empty() ? value.front() : std::string()) +
                line.substr(max.chr);
            p.text->setItemOnlyIfChanged(min.line, tmp);
        }
        else if (min.line == max.line)
        {
            std::vector<std::string> tmp;
            const std::string& line = text[min.line];
            tmp.push_back(line.substr(0, min.chr) + value.front());
            for (size_t i = 1; !value.empty() && i < value.size() - 1; ++i)
            {
                tmp.push_back(value[i]);
            }
            tmp.push_back(line.substr(max.chr) + value.back());
            p.text->replaceItems(min.line, min.line + 1, tmp);
        }
        else if (value.size() <= 1)
        {
            std::string tmp = text[min.line].substr(0, min.chr);
            if (!value.empty())
            {
                tmp += value.front();
            }
            tmp += text[max.line].substr(max.chr);
            p.text->replaceItems(min.line, max.line + 1, { tmp });
        }
        else
        {
            std::vector<std::string> tmp;
            tmp.push_back(text[min.line].substr(0, min.chr) + value.front());
            for (size_t i = 1; !value.empty() && i < value.size() - 1; ++i)
            {
                tmp.push_back(value[i]);
            }
            tmp.push_back(value.back() + text[max.line].substr(max.chr));
            p.text->replaceItems(min.line, max.line + 1, tmp);
        }
    }

    std::ostream& operator << (std::ostream& os, const TextEditPos& value)
    {
        os << value.line << ":" << value.chr;
        return os;
    }

    std::ostream& operator << (std::ostream& os, const TextEditSelection& value)
    {
        os << value.first << "->" << value.second;
        return os;
    }
}
