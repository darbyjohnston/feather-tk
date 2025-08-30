// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/Util.h>

namespace ftk
{
    float getBaseDPI()
    {
#if defined(__APPLE__)
        return 72.F;
#else
        return 96.F;
#endif // __APPLE__
    }
}
