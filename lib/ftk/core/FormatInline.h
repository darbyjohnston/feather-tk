// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <sstream>

namespace ftk
{
    template<typename T>
    inline Format& Format::arg(T value)
    {
        std::stringstream ss;
        ss << value;
        return arg(ss.str());
    }

    inline const std::string& Format::str() const
    {
        return _text;
    }

    inline bool Format::hasError() const
    {
        return _error.size() > 0;
    }

    inline const std::string& Format::getError() const
    {
        return _error;
    }

    inline Format::operator std::string() const
    {
        return _text;
    }
}
