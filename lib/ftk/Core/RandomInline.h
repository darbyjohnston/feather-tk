// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

namespace ftk
{
    template<typename T>
    inline const T& Random::getItem(const std::vector<T>& value)
    {
        return value[getI(0, static_cast<int>(value.size()) - 1)];
    }
}
