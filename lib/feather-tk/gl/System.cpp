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
        
        struct System::Private
        {
        };
        
        System::System(const std::shared_ptr<Context>& context) :
            ISystem(context, "feather_tk::gl::System"),
            _p(new Private)
        {
            FEATHER_TK_P();

            // Initialize SDL.
            SDL_SetHint(SDL_HINT_WINDOWS_DPI_AWARENESS, "permonitorv2");
            if (SDL_Init(SDL_INIT_VIDEO) < 0)
            {
                throw std::runtime_error(Format("Cannot initialize SDL: {0}").
                    arg(SDL_GetError()));
            }
            if (SDL_GL_LoadLibrary(NULL) < 0)
            {
                throw std::runtime_error(Format("Cannot initialize OpenGL: {0}").
                    arg(SDL_GetError()));
            }
        }

        System::~System()
        {
            SDL_Quit();
        }

        std::shared_ptr<System> System::create(const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<System>(new System(context));
        }
    }
}
