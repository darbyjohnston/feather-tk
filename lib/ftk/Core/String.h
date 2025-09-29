// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <string>
#include <vector>

namespace ftk
{
    //! \name Strings
    ///@{
        
    //! Arbitrary C string size.
    constexpr size_t cStringSize = 4096;

    //! String split options.
    enum class SplitOptions
    {
        DiscardEmpty,
        KeepEmpty
    };

    //! Split a string.
    std::vector<std::string> split(
        const std::string&,
        char delimeter,
        SplitOptions = SplitOptions::DiscardEmpty);

    //! Split a string.
    std::vector<std::string> split(
        const std::string&,
        const std::vector<char>& delimeters,
        SplitOptions = SplitOptions::DiscardEmpty);

    //! Join a list of strings.
    std::string join(const std::vector<std::string>&, char delimeter);

    //! Join a list of strings.
    std::string join(const std::vector<std::string>&, const std::string& delimeter);

    //! Join a list of strings with quotes.
    std::string quotes(const std::vector<std::string>&);

    //! Convert to upper case.
    std::string toUpper(const std::string&);

    //! Convert to lower case.
    std::string toLower(const std::string&);

    //! Remove trailing newlines.
    void removeTrailingNewlines(std::string&);

    //! Elide a string.
    std::string elide(const std::string&, size_t = 32);

    //! Case compare.
    enum class CaseCompare
    {
        Sensitive,
        Insensitive
    };

    //! Compare strings.
    bool compare(
        const std::string&,
        const std::string&,
        CaseCompare = CaseCompare::Sensitive);

    //! Does a string contain the sub string?
    bool contains(
        const std::string&,
        const std::string& substr,
        CaseCompare = CaseCompare::Sensitive);

    //! Convert a regular string to a wide string.
    std::wstring toWide(const std::string&);

    //! Convert a wide string to a regular string.
    std::string fromWide(const std::wstring&);

    //! Get filler text.
    std::vector<std::string> getLoremIpsum();

    //! Get filler text.
    std::string getLoremIpsum(size_t lineCount);

    ///@}
}
