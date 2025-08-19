// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/IWidget.h>

namespace feather_tk
{
    //! Base class for windows.
    class IWindow : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::string& objectName,
            const std::shared_ptr<IWidget>& parent);

        IWindow();

    public:
        virtual ~IWindow() = 0;

        //! Get the widget with key focus.
        std::shared_ptr<IWidget> getKeyFocus() const;

        //! Set the widget with key focus.
        void setKeyFocus(const std::shared_ptr<IWidget>&);

        //! Get the next widget to focus.
        std::shared_ptr<IWidget> getNextKeyFocus(const std::shared_ptr<IWidget>&);

        //! Get the previous widget to focus.
        std::shared_ptr<IWidget> getPrevKeyFocus(const std::shared_ptr<IWidget>&);

        //! Get whether tooltips are enabled.
        bool getTooltipsEnabled() const;

        //! Set whether tooltips are enabled.
        void setTooltipsEnabled(bool);

        //! Set the window icons.
        //! 
        //! Icon images should be of type ImageType::RGBA_U8, with no
        //! mirroring, memory alignment of one, and LSB memory endian.
        //!
        //! Window icons are not supported on macOS.
        virtual void setIcons(const std::vector<std::shared_ptr<Image> >&);

        //! Capture a screenshot.
        virtual std::shared_ptr<Image> screenshot(const Box2I & = Box2I(0, 0, -1, -1));

        //! Close the window.
        virtual void close();

        //! Set the window close callback.
        void setCloseCallback(const std::function<void(void)>&);

        void setVisible(bool) override;
        void tickEvent(
            bool parentsVisible,
            bool parentsEnabled,
            const TickEvent&) override;
        void sizeHintEvent(const SizeHintEvent&) override;
        void drawOverlayEvent(const Box2I&, const DrawEvent&) override;

    protected:
        bool _hasSizeUpdate(const std::shared_ptr<IWidget>&) const;
        void _sizeHintEventRecursive(
            const std::shared_ptr<IWidget>&,
            const SizeHintEvent&);

        bool _hasDrawUpdate(const std::shared_ptr<IWidget>&) const;
        void _drawEventRecursive(
            const std::shared_ptr<IWidget>&,
            const Box2I&,
            const DrawEvent&);

        bool _key(Key, bool press, int modifiers);
        void _text(const std::string&);
        void _cursorEnter(bool enter);
        void _cursorPos(const V2I&);
        void _mouseButton(int button, bool press, int modifiers);
        void _scroll(const V2F&, int modifiers);

        void _clipEventRecursive(
            const std::shared_ptr<IWidget>&,
            const Box2I&,
            bool clipped);

        virtual void _drop(const std::vector<std::string>&);

    private:
        enum class UnderCursor
        {
            Hover,
            Tooltip
        };
        std::list<std::shared_ptr<IWidget> > _getUnderCursor(
            UnderCursor,
            const V2I&);
        void _getUnderCursor(
            UnderCursor,
            const std::shared_ptr<IWidget>&,
            const V2I&,
            std::list<std::shared_ptr<IWidget> >&);

        void _hoverUpdate(MouseMoveEvent&);

        void _getKeyFocus(
            const std::shared_ptr<IWidget>&,
            std::list<std::shared_ptr<IWidget> >&);

        void _closeTooltip();

        friend class App;

        FEATHER_TK_PRIVATE();
    };
}
