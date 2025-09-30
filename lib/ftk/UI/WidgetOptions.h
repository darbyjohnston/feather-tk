// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

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

    //! Updates.
    enum class Update
    {
        None = 0,
        Size = 1,
        Draw = 2
    };
}