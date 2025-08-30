// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/WidgetOptions.h>

#include <feather-tk/core/Error.h>
#include <feather-tk/core/String.h>

#include <algorithm>
#include <array>
#include <sstream>

namespace ftk
{
    FTK_ENUM_IMPL(
        Orientation,
        "Horizontal",
        "Vertical");

    FTK_ENUM_IMPL(
        Stretch,
        "Fixed",
        "Expanding");

    FTK_ENUM_IMPL(
        HAlign,
        "Fill",
        "Left",
        "Center",
        "Right");

    FTK_ENUM_IMPL(
        VAlign,
        "Fill",
        "Top",
        "Center",
        "Bottom");
}
