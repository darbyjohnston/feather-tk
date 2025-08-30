// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/RenderOptions.h>

#include <memory>
#include <string>

namespace ftk
{
    namespace gl
    {
        //! \name Utility
        ///@{

        //! Get the major version number from an OpenGL version string.
        int getMajorVersion(const std::string&);

        //! Get the glReadPixels format.
        unsigned int getReadPixelsFormat(ImageType);

        //! Get the glReadPixels type.
        unsigned int getReadPixelsType(ImageType);

        //! Set the alpha blending.
        void setAlphaBlend(AlphaBlend);

        //! Set whether an OpenGL capability is enabled and restore it to the
        //! previous value when finished.
        class SetAndRestore
        {
        public:
            SetAndRestore(unsigned int, bool);

            ~SetAndRestore();

        private:
            FTK_PRIVATE();
        };

        //! Get an OpenGL error label.
        std::string getErrorLabel(unsigned int);
        
        ///@}
    }
}
