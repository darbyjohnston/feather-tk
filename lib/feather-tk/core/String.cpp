// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/core/String.h>

#include <feather-tk/core/Random.h>

#include <algorithm>
#include <codecvt>
#include <locale>

namespace feather_tk
{
    std::vector<std::string> split(
        const std::string& s,
        char delimeter,
        SplitOptions options)
    {
        std::vector<std::string> out;
        bool word = false;
        std::size_t wordStart = 0;
        std::size_t i = 0;
        for (; i < s.size(); ++i)
        {
            if (s[i] != delimeter)
            {
                if (!word)
                {
                    word = true;
                    wordStart = i;
                }
            }
            else
            {
                if (word)
                {
                    word = false;
                    out.push_back(s.substr(wordStart, i - wordStart));
                }
                if (SplitOptions::KeepEmpty == options &&
                    i > 0 &&
                    s[i - 1] == delimeter)
                {
                    out.push_back(std::string());
                }
            }
        }
        if (word)
        {
            out.push_back(s.substr(wordStart, i - wordStart));
        }
        return out;
    }

    std::vector<std::string> split(
        const std::string& s,
        const std::vector<char>& delimeters,
        SplitOptions options)
    {
        std::vector<std::string> out;
        bool word = false;
        std::size_t wordStart = 0;
        std::size_t i = 0;
        for (; i < s.size(); ++i)
        {
            if (std::find(delimeters.begin(), delimeters.end(), s[i]) == delimeters.end())
            {
                if (!word)
                {
                    word = true;
                    wordStart = i;
                }
            }
            else
            {
                if (word)
                {
                    word = false;
                    out.push_back(s.substr(wordStart, i - wordStart));
                }
                if (SplitOptions::KeepEmpty == options &&
                    i > 0 &&
                    std::find(delimeters.begin(), delimeters.end(), s[i - 1]) != delimeters.end())
                {
                    out.push_back(std::string());
                }
            }
        }
        if (word)
        {
            out.push_back(s.substr(wordStart, i - wordStart));
        }
        return out;
    }

    std::string join(const std::vector<std::string>& values, char delimeter)
    {
        std::string out;
        const std::size_t size = values.size();
        for (std::size_t i = 0; i < size; ++i)
        {
            out += values[i];
            if (i < size - 1)
            {
                out += delimeter;
            }
        }
        return out;
    }

    std::string join(const std::vector<std::string>& values, const std::string& delimeter)
    {
        std::string out;
        const std::size_t size = values.size();
        for (std::size_t i = 0; i < size; ++i)
        {
            out += values[i];
            if (i < size - 1)
            {
                out += delimeter;
            }
        }
        return out;
    }

    std::string quotes(const std::vector<std::string>& values)
    {
        std::vector<std::string> tmp;
        for (const auto& value : values)
        {
            tmp.push_back("\"" + value + "\"");
        }
        return join(tmp, ", ");
    }

    std::string toUpper(const std::string& value)
    {
        std::string out;
        for (auto i : value)
        {
            out.push_back(std::toupper(i));
        }
        return out;
    }

    std::string toLower(const std::string& value)
    {
        std::string out;
        for (auto i : value)
        {
            out.push_back(std::tolower(i));
        }
        return out;
    }

    void removeTrailingNewlines(std::string& value)
    {
        size_t size = value.size();
        while (size && ('\n' == value[size - 1] || '\r' == value[size - 1]))
        {
            value.pop_back();
            size = value.size();
        }
    }

    std::string elide(const std::string& value, size_t max)
    {
        std::string out = value.substr(0, max);
        if (out.size() < value.size())
        {
            out.push_back('.');
            out.push_back('.');
            out.push_back('.');
        }
        return out;
    }

    bool compare(
        const std::string& a,
        const std::string& b,
        CaseCompare compare)
    {
        bool out = false;
        switch (compare)
        {
        case CaseCompare::Sensitive:
            out = a == b;
            break;
        case CaseCompare::Insensitive:
            out = toLower(a) == toLower(b);
            break;
        }
        return out;
    }

    bool contains(
        const std::string& input,
        const std::string& substr,
        CaseCompare compare)
    {
        size_t i = std::string::npos;
        switch (compare)
        {
        case CaseCompare::Sensitive:
            i = input.find(substr);
            break;
        case CaseCompare::Insensitive:
            i = toLower(input).find(toLower(substr));
            break;
        }
        return i != std::string::npos;
    }

    std::wstring toWide(const std::string& value)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
        return converter.from_bytes(value);
    }

    std::string fromWide(const std::wstring& value)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
        return converter.to_bytes(value);
    }

    std::vector<std::string> getLoremIpsum()
    {
        return
        {
            "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.",
            "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.",
            "Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.",
            "Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
        };
    }

    namespace
    {
        const size_t randSize = 20;
        const size_t sentencesInAParagraph = 5;
    }

    std::string getLoremIpsum(size_t lineCount)
    {
        std::string out;

        const std::vector<std::string> lines = getLoremIpsum();

        Random rand;
        std::vector<size_t> rands;
        std::vector<bool> paragraphs;
        for (size_t i = 0; i < randSize; ++i)
        {
            rands.push_back(rand.getI(1, lines.size() - 1));
            paragraphs.push_back(
                sentencesInAParagraph == rand.getI(sentencesInAParagraph));
        }

        size_t counter = 0;
        for (size_t i = 0; i < lineCount; ++i)
        {
            counter += rands[i % randSize];
            out.append(lines[counter % lines.size()]);
            if (i < lineCount - 1)
            {
                //! \todo Remove this newline when text wrapping is supported.
                out.push_back('\n');

                if (paragraphs[i % randSize])
                {
                    out.push_back('\n');
                }
            }
        }
        return out;
    }
}
