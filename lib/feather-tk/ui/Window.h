// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/IWindow.h>

namespace feather_tk
{
    //! Window.
    class Window : public IWindow
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<App>&,
            const std::string& name,
            const Size2I&);

        Window();

    public:
        virtual ~Window();

        //! Create a new window.
        static std::shared_ptr<Window> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<App>&,
            const std::string& name,
            const Size2I&);

        //! Get the window ID.
        uint32_t getID() const;

        //! Get the window size.
        const Size2I& getSize() const;

        //! Set the window size.
        void setSize(const Size2I&);

        //! Get whether the window is full screen.
        bool isFullScreen() const;

        //! Observe whether the window is full screen.
        std::shared_ptr<IObservableValue<bool> > observeFullScreen() const;

        //! Set whether the window is full screen.
        void setFullScreen(bool, int screen = -1);

        //! Get which screen the window is on.
        int getScreen() const;

        //! Get whether the window is floating on top.
        bool isFloatOnTop() const;

        //! Observe whether the window is floating on top.
        std::shared_ptr<IObservableValue<bool> > observeFloatOnTop() const;

        //! Set whether the window is floating on top.
        void setFloatOnTop(bool);

        //! Get the window frame buffer size.
        const Size2I& getFrameBufferSize() const;

        //! Get the frame buffer type.
        ImageType getFrameBufferType() const;

        //! Observe the frame buffer type.
        std::shared_ptr<IObservableValue<ImageType> > observeFrameBufferType() const;

        //! Set the frame buffer type.
        void setFrameBufferType(ImageType);

        //! Get the content scale.
        float getContentScale() const;

        //! Get the display scale.
        float getDisplayScale() const;

        //! Observe the display scale.
        std::shared_ptr<IObservableValue<float> > observeDisplayScale() const;

        //! Set the display scale. A value of zero will set the display scale
        //! automatically.
        void setDisplayScale(float);

        void setIcons(const std::vector<std::shared_ptr<Image> >&) override;
        std::shared_ptr<Image> screenshot(const Box2I& = Box2I(0, 0, -1, -1)) override;
        void setCloseCallback(const std::function<void(void)>&) override;

        void setGeometry(const Box2I&) override;
        void setVisible(bool) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    protected:
        virtual std::shared_ptr<IRender> _createRender(const std::shared_ptr<Context>&);

        void _sizeUpdate();

        virtual void _update(
            const std::shared_ptr<FontSystem>&,
            const std::shared_ptr<IconSystem>&,
            const std::shared_ptr<Style>&);

        void _makeCurrent();

    private:
        friend class App;

        FEATHER_TK_PRIVATE();
    };
}
