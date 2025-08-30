// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

//! Project namespace
namespace ftk
{
    //! \name Assert
    ///@{
        
    //! Assert (for convenience use the FTK_ASSERT macro).
    void ftk_assert(const char* file, int line);

    ///@}
}

//! Assert macro.
#if defined(FTK_ASSERT)
#undef FTK_ASSERT
#define FTK_ASSERT(value) \
    if (!(value)) \
        ftk::ftk_assert(__FILE__, __LINE__)
#else // FTK_ASSERT
#define FTK_ASSERT(value)
#endif // FTK_ASSERT

