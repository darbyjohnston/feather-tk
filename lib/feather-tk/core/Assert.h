// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

//! Project namespace
namespace feather_tk
{
    //! \name Assert
    ///@{
        
    //! Assert (for convenience use the FEATHER_TK_ASSERT macro).
    void ftk_assert(const char* file, int line);

    ///@}
}

//! Assert macro.
#if defined(FEATHER_TK_ASSERT)
#undef FEATHER_TK_ASSERT
#define FEATHER_TK_ASSERT(value) \
    if (!(value)) \
        feather_tk::ftk_assert(__FILE__, __LINE__)
#else // FEATHER_TK_ASSERT
#define FEATHER_TK_ASSERT(value)
#endif // FEATHER_TK_ASSERT

