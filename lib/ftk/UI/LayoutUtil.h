// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/WidgetOptions.h>

#include <ftk/Core/Box.h>

namespace ftk
{
    //! \name Layouts
    ///@{
        
    //! Align within the given box.
    Box2I align(
        const Box2I&  box,
        const Size2I& sizeHint,
        HAlign        hAlign,
        VAlign        vAlign);

    //! Get a format string for the given number.
    std::string format(int);

    //! Get a format string for the given number.
    std::string format(float, int precision);
        
    ///@}
}
