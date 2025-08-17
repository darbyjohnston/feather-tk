// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/Image.h>

namespace feather_tk
{
    class Context;

    namespace gl
    {
        //! \name Windows
        ///@{
        
        //! OpenGL window options.
        enum class WindowOptions
        {
            None         = 0,
            Visible      = 1,
            DoubleBuffer = 2,
            MakeCurrent  = 4
        };

        //! OpenGL window.
        class Window : public std::enable_shared_from_this<Window>
        {
            FEATHER_TK_NON_COPYABLE(Window);

        protected:
            Window(
                const std::shared_ptr<Context>&,
                const std::string& name,
                const Size2I&,
                int options,
                const std::shared_ptr<Window>& share);

        public:
            virtual ~Window();

            //! Create a new window.
            static std::shared_ptr<Window> create(
                const std::shared_ptr<Context>&,
                const std::string& name,
                const Size2I&,
                int options =
                    static_cast<int>(WindowOptions::Visible) |
                    static_cast<int>(WindowOptions::DoubleBuffer) |
                    static_cast<int>(WindowOptions::MakeCurrent),
                const std::shared_ptr<Window>& share = nullptr);
        
            //! Get the window ID.
            uint32_t getID() const;

            //! Set the window size.
            void setSize(const Size2I&);

            //! Show the window.
            void show();

            //! Hide the window.
            void hide();

            //! Set the window icons.
            //! 
            //! Icon images should be of type ImageType::RGBA_U8, with no
            //! mirroring, memory alignment of one, and LSB memory endian.
            //!
            //! Window icons are not supported on macOS.
            void setIcons(const std::vector<std::shared_ptr<Image> >&);

            //! Make the OpenGL context current.
            void makeCurrent();

            //! Get which screen the window is on.
            int getScreen() const;

            //! Get whether the window is in full screen mode.
            bool isFullScreen() const;

            //! Set whether the window is in full screen mode.
            void setFullScreen(bool, int screen = -1);

            //! Get whether the window is floating on top.
            bool isFloatOnTop() const;

            //! Set whether the window is floating on top.
            void setFloatOnTop(bool);

            //! Swap the buffers.
            void swap();

        private:
            FEATHER_TK_PRIVATE();
        };
        
        ///@}
    }
}

