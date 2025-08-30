// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/core/Error.h>

#include <feather-tk/core/String.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX
#include <windows.h>

namespace ftk
{
    std::string getLastError()
    {
        std::string out;
        const DWORD dw = GetLastError();
        if (dw != ERROR_SUCCESS)
        {
            TCHAR buf[cStringSize];
            FormatMessage(
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                dw,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                buf,
                cStringSize,
                NULL);
            out = std::string(buf, lstrlen(buf));
            removeTrailingNewlines(out);
        }
        return out;
    }
}