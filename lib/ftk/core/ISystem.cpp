// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/core/ISystem.h>

#include <ftk/core/Context.h>
#include <ftk/core/LogSystem.h>

namespace ftk
{
    ISystem::ISystem(
        const std::shared_ptr<Context>& context,
        const std::string& name) :
        _context(context),
        _name(name)
    {
        if (auto logSystem = context->getSystem<LogSystem>())
        {
            logSystem->print(_name, "Create...");
        }
    }

    ISystem::~ISystem()
    {
        if (auto context = _context.lock())
        {
            if (auto logSystem = context->getSystem<LogSystem>())
            {
                logSystem->print(_name, "Destroy...");
            }
        }
    }

    void ISystem::tick()
    {}

    std::chrono::milliseconds ISystem::getTickTime() const
    {
        return std::chrono::milliseconds(0);
    }
}