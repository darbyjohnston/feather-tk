// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <ftk/Core/PNG.h>

#include <png.h>

namespace ftk
{
    namespace png
    {
        //! PNG error.
        struct ErrorStruct
        {
            std::string message;
        };
    }
}

extern "C"
{
    void pngErrorFunc(png_structp, png_const_charp);
    void pngWarningFunc(png_structp, png_const_charp);
}
