// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/Core/Time.h>

#include <ftk/Core/Math.h>

#include <cmath>
#include <utility>
#include <vector>

namespace ftk
{
    void sleep(
        const std::chrono::microseconds& value,
        const std::chrono::steady_clock::time_point& t0,
        const std::chrono::steady_clock::time_point& t1)
    {
        const std::chrono::duration<double> diff = t1 - t0;
        const long long diffClamped = clamp(
            static_cast<int64_t>(diff.count() * 1000000),
            static_cast<int64_t>(0),
            static_cast<int64_t>(value.count()));
        sleep(std::chrono::microseconds(value.count() - diffClamped));
    }

    std::pair<int, int> toRational(double value)
    {
        const std::vector<std::pair<int, int> > common =
        {
            std::make_pair(6, 1),
            std::make_pair(12, 1),
            std::make_pair(18, 1),
            std::make_pair(24000, 1001),
            std::make_pair(24, 1),
            std::make_pair(25, 1),
            std::make_pair(30000, 1001),
            std::make_pair(30, 1),
            std::make_pair(48, 1),
            std::make_pair(60000, 1001),
            std::make_pair(60, 1)
        };
        const double tolerance = 0.01;
        for (const auto& i : common)
        {
            const double diff = fabs(value - i.first / static_cast<double>(i.second));
            if (diff < tolerance)
            {
                return i;
            }
        }
        return std::make_pair(static_cast<int>(value), 1);
    }
}