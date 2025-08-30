// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

namespace ftk
{
    template<typename T>
    inline std::shared_ptr<T> Context::getSystem() const
    {
        for (const auto& i : _systems)
        {
            if (auto system = std::dynamic_pointer_cast<T>(i))
            {
                return system;
            }
        }
        return nullptr;
    }

    inline const std::shared_ptr<LogSystem>& Context::getLogSystem() const
    {
        return _logSystem;
    }
}
