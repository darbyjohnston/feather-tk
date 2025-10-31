// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <ftk/Core/ISystem.h>

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
