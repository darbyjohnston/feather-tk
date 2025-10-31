// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <memory>

namespace ftk
{
    class Context;

    //! OpenGL support
    namespace gl
    {
        //! Initialize the library.
        void init(const std::shared_ptr<Context>&);

        //! Initialize GLAD.
        void initGLAD();
    }
}

