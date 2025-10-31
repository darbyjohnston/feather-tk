// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#include <ftk/UI/WidgetOptions.h>

#include <ftk/Core/Error.h>
#include <ftk/Core/String.h>

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
