// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

namespace ftk
{
    inline const std::weak_ptr<Context>& ISystem::getContext() const
    {
        return _context;
    }

    inline const std::string& ISystem::getName() const
    {
        return _name;
    }
}
