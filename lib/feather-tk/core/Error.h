// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <stdexcept>

namespace ftk
{
    //! \name Errors
    ///@{
        
    //! Parse error.
    class ParseError : public std::invalid_argument
    {
    public:
        ParseError();
    };
        
#if defined(_WINDOWS)
    //! Get an error string from a Windows system call.
    std::string getLastError();
#endif // _WINDOWS

    ///@}
}
