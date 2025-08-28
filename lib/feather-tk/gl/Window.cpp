// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/gl/Window.h>

#include <feather-tk/gl/GL.h>
#include <feather-tk/gl/Init.h>
#include <feather-tk/gl/Util.h>

#include <feather-tk/core/Box.h>
#include <feather-tk/core/Context.h>
#include <feather-tk/core/Format.h>
#include <feather-tk/core/LogSystem.h>
#include <feather-tk/core/String.h>

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
            std::weak_ptr<LogSystem> logSystem;
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

            p.logSystem = context->getLogSystem();

            SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
            const bool doubleBuffer = options & static_cast<int>(WindowOptions::DoubleBuffer);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, doubleBuffer);
#if defined(FEATHER_TK_API_GL_4_1)
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
#elif defined(FEATHER_TK_API_GLES_2)
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#endif // FEATHER_TK_API_GL_4_1
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
                throw std::runtime_error(Format("Cannot create window: {0}").
                    arg(SDL_GetError()));
            }

            p.sdlGLContext = SDL_GL_CreateContext(p.sdlWindow);
            if (!p.sdlGLContext)
            {
                throw std::runtime_error(Format("Cannot create OpenGL context: {0}").
                    arg(SDL_GetError()));
            }
            if (options & static_cast<int>(WindowOptions::DoubleBuffer))
            {
                SDL_GL_SetSwapInterval(1);
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

            std::string glVendor;
            std::string glRenderer;
            std::string glVersion;
            int glVersionMajor = 0;
            if (const GLubyte* glString = glGetString(GL_VENDOR))
            {
                glVendor = std::string((const char*)glString);
            }
            if (const GLubyte* glString = glGetString(GL_RENDERER))
            {
                glRenderer = std::string((const char*)glString);
            }
            if (const GLubyte* glString = glGetString(GL_VERSION))
            {
                glVersion = std::string((const char*)glString);
                glVersionMajor = getMajorVersion(glVersion);
            }
            //! \todo Shouldn't window creation fail if we didn't get the
            //! requested OpenGL version?
#if defined(FEATHER_TK_API_GL_4_1)
            if (glVersionMajor < 4)
#elif defined(FEATHER_TK_API_GLES_2)
            if (glVersionMajor < 2)
#endif // FEATHER_TK_API_GL_4_1
            {
                throw std::runtime_error(Format("Unsupported OpenGL version: {0}").
                    arg(glVersionMajor));
            }

            if (auto logSystem = p.logSystem.lock())
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
                    arg(glVendor).
                    arg(glRenderer).
                    arg(glVersion));
            }

            if (!(options & static_cast<int>(WindowOptions::MakeCurrent)))
            {
                clearCurrent();
            }
        }
        
        Window::~Window()
        {
            FEATHER_TK_P();
            if (p.sdlGLContext)
            {
                SDL_GL_DeleteContext(p.sdlGLContext);
            }
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
            if (SDL_GL_MakeCurrent(p.sdlWindow, p.sdlGLContext) < 0)
            {
                if (auto logSystem = p.logSystem.lock())
                {
                    logSystem->print(
                        "feather_tk::gl::Window",
                        Format("Cannot make context current: {0}").arg(SDL_GetError()),
                        LogType::Error);
                }
            }
        }

        void Window::clearCurrent()
        {
            FEATHER_TK_P();
            if (SDL_GL_MakeCurrent(p.sdlWindow, nullptr) < 0)
            {
                if (auto logSystem = p.logSystem.lock())
                {
                    logSystem->print(
                        "feather_tk::gl::Window",
                        Format("Cannot make context done: {0}").arg(SDL_GetError()),
                        LogType::Error);
                }
            }
        }

        int Window::getScreen() const
        {
            return 0;
        }

        bool Window::isFullScreen() const
        {
            return _p->fullScreen;
        }

        void Window::setFullScreen(bool value)
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
