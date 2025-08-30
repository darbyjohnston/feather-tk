// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/core/Util.h>

#include <chrono>
#include <memory>
#include <string>

namespace ftk
{
    class Context;

    //! Base class for systems.
    class ISystem : public std::enable_shared_from_this<ISystem>
    {
        FTK_NON_COPYABLE(ISystem);

    protected:
        ISystem(
            const std::shared_ptr<Context>&,
            const std::string& name);

    public:
        virtual ~ISystem() = 0;

        //! Get the context.
        const std::weak_ptr<Context>& getContext() const;

        //! Get the system name.
        const std::string& getName() const;

        //! Tick the system.
        virtual void tick();

        //! Get the system tick time interval.
        virtual std::chrono::milliseconds getTickTime() const;

    protected:
        std::weak_ptr<Context> _context;
        std::string _name;
    };
}

#include <ftk/core/ISystemInline.h>

