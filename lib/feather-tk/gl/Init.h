// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <memory>

namespace feather_tk
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

