// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/GL/Init.h>

#include <ftk/GL/GL.h>
#include <ftk/GL/System.h>

#include <ftk/Core/Context.h>
#include <ftk/Core/Format.h>

#include <SDL2/SDL.h>

#include <stdexcept>

namespace ftk
{
    namespace gl
    {
        void init(const std::shared_ptr<Context>& context)
        {
            if (!context->getSystem<System>())
            {
                context->addSystem(System::create(context));
            }
        }

        void initGLAD()
        {
            int r = 0;
#if defined(FTK_API_GL_4_1)
            r = gladLoaderLoadGL();
#elif defined(FTK_API_GLES_2)
            r = gladLoadGLES2Loader((GLADloadproc)SDL_GL_GetProcAddress);
#endif // FTK_API_GL_4_1
            if (0 == r)
            {
                throw std::runtime_error(Format("Cannot initialize GLAD: {0}").arg(r));
            }
        }
    }
}
