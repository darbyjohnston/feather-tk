// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/gl/System.h>

#include <feather-tk/gl/GL.h>

#include <feather-tk/core/Context.h>
#include <feather-tk/core/Format.h>
#include <feather-tk/core/LogSystem.h>
#include <feather-tk/core/String.h>

#include <SDL2/SDL.h>

#include <iostream>

namespace feather_tk
{
    namespace gl
    {
        bool MonitorInfo::operator == (const MonitorInfo& other) const
        {
            return
                name == other.name &&
                size == other.size &&
                colorBits == other.colorBits &&
                refreshRate == other.refreshRate &&
                contentScale == other.contentScale &&
                pos == other.pos &&
                physicalSizeMM == other.physicalSizeMM;
        }

        bool MonitorInfo::operator != (const MonitorInfo& other) const
        {
            return !(*this == other);
        }
        
        struct System::Private
        {
            bool sdlInit = false;
            std::shared_ptr<ObservableList<MonitorInfo> > monitors;
            std::shared_ptr<ListObserver<MonitorInfo> > monitorsObserver;
        };
        
        System::System(const std::shared_ptr<Context>& context) :
            ISystem(context, "feather_tk::gl::System"),
            _p(new Private)
        {
            FEATHER_TK_P();

            // Initialize SDL.
            SDL_SetHint(SDL_HINT_WINDOWS_DPI_SCALING, "1");
            if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
            {
                throw std::runtime_error("Cannot initialize SDL");
            }
            SDL_GL_LoadLibrary(NULL);
            p.sdlInit = true;
            //auto logSystem = context->getSystem<LogSystem>();

            p.monitors = ObservableList<MonitorInfo>::create();
            p.monitorsObserver = ListObserver<MonitorInfo>::create(
                p.monitors,
                [this](const std::vector<MonitorInfo>& value)
                {
                    if (auto context = _context.lock())
                    {
                        std::vector<std::string> lines;
                        for (const auto& i : value)
                        {
                            lines.push_back(Format("Monitor: {0}").arg(i.name));
                            lines.push_back(Format("    Size: {0}").arg(i.size));
                            lines.push_back(Format("    Color bits: {0} {1} {2}").
                                arg(i.colorBits[0]).
                                arg(i.colorBits[1]).
                                arg(i.colorBits[2]));
                            lines.push_back(Format("    Referesh rate: {0}").arg(i.refreshRate));
                            lines.push_back(Format("    Content scale: {0}").arg(i.contentScale));
                            lines.push_back(Format("    Position: {0}").arg(i.pos));
                            lines.push_back(Format("    Physical size mm: {0}").arg(i.physicalSizeMM));
                        }
                        auto logSystem = context->getSystem<LogSystem>();
                        logSystem->print(
                            "feather_tk::gl::System",
                            join(lines, '\n'));
                    }
                });
        }

        System::~System()
        {
            FEATHER_TK_P();
            if (p.sdlInit)
            {
                SDL_Quit();
            }
        }

        std::shared_ptr<System> System::create(const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<System>(new System(context));
        }

        std::shared_ptr<IObservableList<MonitorInfo> > System::observeMonitors() const
        {
            return _p->monitors;
        }
    }
}
