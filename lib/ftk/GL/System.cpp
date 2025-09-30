// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/GL/System.h>

#include <ftk/GL/GL.h>

#include <ftk/Core/Context.h>
#include <ftk/Core/Format.h>
#include <ftk/Core/LogSystem.h>
#include <ftk/Core/String.h>

#include <SDL2/SDL.h>

#include <iostream>

namespace ftk
{
    namespace gl
    {
        
        struct System::Private
        {
        };
        
        System::System(const std::shared_ptr<Context>& context) :
            ISystem(context, "ftk::gl::System"),
            _p(new Private)
        {
            FTK_P();

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
