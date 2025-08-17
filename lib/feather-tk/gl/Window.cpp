// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/gl/Window.h>

#include <feather-tk/gl/GL.h>
#include <feather-tk/gl/Init.h>

#include <feather-tk/core/Box.h>
#include <feather-tk/core/Context.h>
#include <feather-tk/core/Format.h>
#include <feather-tk/core/LogSystem.h>

#include <SDL2/SDL.h>

#include <algorithm>
#include <iostream>
#include <vector>

namespace feather_tk
{
    namespace gl
    {
        struct Window::Private
        {
            std::weak_ptr<Context> context;
            SDL_Window* sdlWindow = nullptr;
            SDL_GLContext sdlGLContext = nullptr;
            V2I pos;
            std::vector<std::shared_ptr<Image> > icons;
            bool fullScreen = false;
            Size2I restoreSize;
            bool floatOnTop = false;
        };
        
        Window::Window(
            const std::shared_ptr<Context>& context,
            const std::string& name,
            const Size2I& size,
            int options,
            const std::shared_ptr<Window>& share) :
            _p(new Private)
        {
            FEATHER_TK_P();

            p.context = context;

#if defined(FEATHER_TK_API_GL_4_1)
            SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#elif defined(FEATHER_TK_API_GLES_2)
            SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#endif // FEATHER_TK_API_GL_4_1
            if (options & static_cast<int>(WindowOptions::DoubleBuffer))
            {
                SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            }
            uint32_t sdlWindowFlags =
                SDL_WINDOW_OPENGL |
                SDL_WINDOW_RESIZABLE |
                SDL_WINDOW_ALLOW_HIGHDPI;
            if (options & static_cast<int>(WindowOptions::Visible))
            {
                sdlWindowFlags |= SDL_WINDOW_SHOWN;
            }
            else
            {
                sdlWindowFlags |= SDL_WINDOW_HIDDEN;
            }
            p.sdlWindow = SDL_CreateWindow(
                name.c_str(),
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                size.w,
                size.h,
                sdlWindowFlags);
            if (!p.sdlWindow)
            {
                throw std::runtime_error("Cannot create window");
            }

            p.sdlGLContext = SDL_GL_CreateContext(p.sdlWindow);
            if (!p.sdlWindow)
            {
                throw std::runtime_error("Cannot create OpenGL context");
            }
            if (options & static_cast<int>(WindowOptions::DoubleBuffer))
            {
                SDL_GL_SetSwapInterval(1);
            }
            if (options & static_cast<int>(WindowOptions::MakeCurrent))
            {
                makeCurrent();
            }

            initGLAD();
#if defined(FEATHER_TK_API_GL_4_1_Debug)
            GLint flags = 0;
            glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
            if (flags & static_cast<GLint>(GL_CONTEXT_FLAG_DEBUG_BIT))
            {
                glEnable(GL_DEBUG_OUTPUT);
                glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
                glDebugMessageCallback(glDebugOutput, nullptr);
                glDebugMessageControl(
                    static_cast<GLenum>(GL_DONT_CARE),
                    static_cast<GLenum>(GL_DONT_CARE),
                    static_cast<GLenum>(GL_DONT_CARE),
                    0,
                    nullptr,
                    GL_TRUE);
            }
#endif // FEATHER_TK_API_GL_4_1_Debug

            if (auto logSystem = context->getSystem<LogSystem>())
            {
                logSystem->print(
                    "feather_tk::gl::Window",
                    Format(
                        "New window:\n"
                        "    Size: {0}\n"
                        "    OpenGL vendor: {1}\n"
                        "    OpenGL renderer: {2}\n"
                        "    OpenGL version: {3}").
                    arg(size).
                    arg(glGetString(GL_VENDOR)).
                    arg(glGetString(GL_RENDERER)).
                    arg(glGetString(GL_VERSION)));
            }
        }
        
        Window::~Window()
        {
            FEATHER_TK_P();
            if (p.sdlWindow)
            {
                SDL_DestroyWindow(p.sdlWindow);
            }
        }

        std::shared_ptr<Window> Window::create(
            const std::shared_ptr<Context>& context,
            const std::string& name,
            const Size2I& size,
            int options,
            const std::shared_ptr<Window>& share)
        {
            return std::shared_ptr<Window>(new Window(context, name, size, options, share));
        }

        uint32_t Window::getID() const
        {
            return SDL_GetWindowID(_p->sdlWindow);
        }

        void Window::setSize(const Size2I& value)
        {
            setFullScreen(false);
            SDL_SetWindowSize(_p->sdlWindow, value.w, value.h);
        }

        void Window::show()
        {
            SDL_ShowWindow(_p->sdlWindow);
        }

        void Window::hide()
        {
            setFullScreen(false);
            SDL_HideWindow(_p->sdlWindow);
        }

        void Window::setIcons(const std::vector<std::shared_ptr<Image> >& icons)
        {
        }

        void Window::makeCurrent()
        {
            FEATHER_TK_P();
            SDL_GL_MakeCurrent(p.sdlWindow, p.sdlGLContext);
        }

        int Window::getScreen() const
        {
            return 0;
        }

        bool Window::isFullScreen() const
        {
            return _p->fullScreen;
        }

        void Window::setFullScreen(bool value, int screen)
        {
            FEATHER_TK_P();
            if (value == p.fullScreen)
                return;
            p.fullScreen = value;
            if (p.fullScreen)
            {
                SDL_GetWindowPosition(p.sdlWindow, &p.pos.x, &p.pos.y);
                SDL_GetWindowSize(p.sdlWindow, &p.restoreSize.w, &p.restoreSize.h);
                SDL_SetWindowFullscreen(p.sdlWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
            }
            else
            {
                SDL_SetWindowFullscreen(p.sdlWindow, 0);
                SDL_SetWindowPosition(p.sdlWindow, p.pos.x, p.pos.y);
                SDL_SetWindowSize(p.sdlWindow, p.restoreSize.w, p.restoreSize.h);
            }
        }

        bool Window::isFloatOnTop() const
        {
            return _p->floatOnTop;
        }

        void Window::setFloatOnTop(bool value)
        {
            FEATHER_TK_P();
            if (value == p.floatOnTop)
                return;
            p.floatOnTop = value;
        }

        void Window::swap()
        {
            SDL_GL_SwapWindow(_p->sdlWindow);
        }
    }
}
