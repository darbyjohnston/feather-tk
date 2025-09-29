// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/Core/Assert.h>

#include <iostream>

#include <stdlib.h>

namespace ftk
{
    void ftk_assert(const char* file, int line)
    {
        std::cout << "ASSERT: " << file << ":" << line << std::endl;
        abort();
    }
}
