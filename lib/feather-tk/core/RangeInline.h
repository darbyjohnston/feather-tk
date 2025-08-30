// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <algorithm>

namespace ftk
{
    template<typename T>
    constexpr Range<T>::Range() :
        _min(static_cast<T>(0)),
        _max(static_cast<T>(0))
    {}

    template<typename T>
    constexpr Range<T>::Range(T min, T max) :
        _min(std::min(min, max)),
        _max(std::max(min, max))
    {}

    template<typename T>
    constexpr T Range<T>::min() const
    {
        return _min;
    }

    template<typename T>
    constexpr T Range<T>::max() const
    {
        return _max;
    }

    template<typename T>
    constexpr bool Range<T>::operator == (const Range<T>& value) const
    {
        return _min == value._min && _max == value._max;
    }

    template<typename T>
    constexpr bool Range<T>::operator != (const Range<T>& value) const
    {
        return !(*this == value);
    }

    template<typename T>
    constexpr bool Range<T>::operator < (const Range<T>& value) const
    {
        return _min < value._min;
    }

    template<typename T>
    inline bool contains(const Range<T>& range, T value)
    {
        return value >= range.min() && value <= range.max();
    }

    template<typename T>
    inline bool intersects(const Range<T>& range, const Range<T>& value)
    {
        return !(
            value.max() < range.min() ||
            value.min() > range.max());
    }

    template<typename T>
    inline Range<T> expand(const Range<T>& range, T value)
    {
        return Range<T>(
            std::min(range.min(), value),
            std::max(range.max(), value));
    }

    template<typename T>
    inline Range<T> expand(const Range<T>& range, const Range<T>& value)
    {
        return Range<T>(
            std::min(range.min(), value.min()),
            std::max(range.max(), value.max()));
    }

    template<typename T>
    inline std::ostream& operator << (std::ostream& os, const Range<T>& v)
    {
        os << v.min() << " " << v.max();
        return os;
    }

    template<typename T>
    inline std::istream& operator >> (std::istream& is, Range<T>& v)
    {
        T min(0);
        T max(0);
        is >> min;
        is >> max;
        v = Range<T>(min, max);
        return is;
    }
}
