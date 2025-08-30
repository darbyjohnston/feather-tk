// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/ISystem.h>

namespace ftk
{
    namespace gl
    {
        //! OpenGL system.
        class System : public ISystem
        {
        protected:
            System(const std::shared_ptr<Context>&);

        public:
            virtual ~System();

            //! Create a new system.
            static std::shared_ptr<System> create(const std::shared_ptr<Context>&);
        
        private:
            FTK_PRIVATE();
        };
    }
}
