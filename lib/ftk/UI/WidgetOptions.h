// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <ftk/Core/Util.h>

#include <iostream>
#include <string>
#include <vector>

namespace ftk
{
    //! Orientation.
    enum class Orientation
    {
        Horizontal,
        Vertical,

        Count,
        First = Horizontal
    };
    FTK_ENUM(Orientation);

    //! Layout stretch.
    enum class Stretch
    {
        Fixed,
        Expanding,

        Count,
        First = Fixed
    };
    FTK_ENUM(Stretch);

    //! Horizontal alignment.
    enum class HAlign
    {
        Fill,
        Left,
        Center,
        Right,

        Count,
        First = Left
    };
    FTK_ENUM(HAlign);

    //! Vertical alignment.
    enum class VAlign
    {
        Fill,
        Top,
        Center,
        Bottom,

        Count,
        First = Top
    };
    FTK_ENUM(VAlign);
}