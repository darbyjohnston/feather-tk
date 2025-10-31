// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#include <ftk/UI/Util.h>

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
