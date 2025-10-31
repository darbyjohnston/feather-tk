// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#include <ftk/Core/Time.h>

#include <thread>

namespace ftk
{
    void sleep(const std::chrono::microseconds& value)
    {
        std::this_thread::sleep_for(value);
    }
}
