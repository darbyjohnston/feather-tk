// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#include <algorithm>

namespace ftk
{
    constexpr float deg2rad(float value)
    {
        return value / 360.F * pi2;
    }

    constexpr float rad2deg(float value)
    {
        return value / pi2 * 360.F;
    }

    template<typename T>
    constexpr T clamp(T value, T min, T max)
    {
        return std::min(std::max(value, min), max);
    }

    template<class T, class U>
    constexpr T lerp(U value, T min, T max)
    {
        return min + T(value * (max - min));
    }

    constexpr float smoothStep(float value, float min, float max)
    {
        return lerp(value * value * (3.F - (2.F * value)), min, max);
    }

    constexpr double smoothStep(double value, double min, double max)
    {
        return lerp(value * value * (3. - (2. * value)), min, max);
    }
}
