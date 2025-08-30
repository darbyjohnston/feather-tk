// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/core/Context.h>

#include <ftk/core/FontSystem.h>
#include <ftk/core/Format.h>
#include <ftk/core/ImageIO.h>
#include <ftk/core/OS.h>
#include <ftk/core/Timer.h>

namespace ftk
{
    void Context::_init()
    {
        _logSystem = LogSystem::create(shared_from_this());
        addSystem(_logSystem);
        const auto systemInfo = getSystemInfo();
        _logSystem->print(
            "ftk::Context",
            Format(
                "System information:\n"
                "    Name:  {0}\n"
                "    Cores: {1}\n"
                "    RAM:   {2}GB").
            arg(systemInfo.name).
            arg(systemInfo.cores).
            arg(systemInfo.ramGB));

        addSystem(FontSystem::create(shared_from_this()));
        addSystem(ImageIO::create(shared_from_this()));
        addSystem(TimerSystem::create(shared_from_this()));
    }

    Context::~Context()
    {}

    std::shared_ptr<Context> Context::create()
    {
        auto out = std::shared_ptr<Context>(new Context);
        out->_init();
        return out;
    }

    void Context::addSystem(const std::shared_ptr<ISystem>& system)
    {
        _systems.push_front(system);
        _systemTimes[system] = std::chrono::steady_clock::now();
    }

    const std::list<std::shared_ptr<ISystem> >& Context::getSystems() const
    {
        return _systems;
    }

    std::shared_ptr<ISystem> Context::getSystemByName(const std::string& name) const
    {
        std::shared_ptr<ISystem> out;
        for (const auto& system : _systems)
        {
            if (name == system->getName())
            {
                out = system;
                break;
            }
        }
        return out;
    }

    void Context::log(const std::string& prefix, const std::string& value, LogType type)
    {
        _logSystem->print(prefix, value, type);
    }

    void Context::tick()
    {
        const auto now = std::chrono::steady_clock::now();
        for (auto& i : _systemTimes)
        {
            const auto tickTime = i.first->getTickTime();
            if (tickTime > std::chrono::milliseconds(0) &&
                (i.second + i.first->getTickTime()) <= now)
            {
                i.first->tick();
                i.second = now;
            }
        }
    }
}