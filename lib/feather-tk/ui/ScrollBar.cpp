// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/ScrollBar.h>

#include <feather-tk/ui/DrawUtil.h>

#include <optional>

namespace ftk
{
    struct ScrollBar::Private
    {
        Orientation orientation = Orientation::Horizontal;
        int scrollSize = 0;
        int scrollPos = 0;
        std::function<void(int)> scrollPosCallback;

        struct SizeData
        {
            std::optional<float> displayScale;
            int handle = 0;
            int border = 0;
        };
        SizeData size;

        struct MouseData
        {
            int pressedScrollPos = 0;
        };
        MouseData mouse;
    };

    void ScrollBar::_init(
        const std::shared_ptr<Context>& context,
        Orientation orientation,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "ftk::ScrollBar", parent);
        FTK_P();
        setBackgroundRole(ColorRole::Base);
        _setMouseHoverEnabled(true);
        _setMousePressEnabled(true);
        p.orientation = orientation;
    }

    ScrollBar::ScrollBar() :
        _p(new Private)
    {}

    ScrollBar::~ScrollBar()
    {}

    std::shared_ptr<ScrollBar> ScrollBar::create(
        const std::shared_ptr<Context>& context,
        Orientation orientation,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<ScrollBar>(new ScrollBar);
        out->_init(context, orientation, parent);
        return out;
    }

    int ScrollBar::getScrollSize() const
    {
        return _p->scrollSize;
    }

    void ScrollBar::setScrollSize(int value)
    {
        FTK_P();
        if (value == p.scrollSize)
            return;
        p.scrollSize = value;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    int ScrollBar::getScrollPos() const
    {
        return _p->scrollPos;
    }

    void ScrollBar::setScrollPos(int value)
    {
        FTK_P();
        if (value == p.scrollPos)
            return;
        p.scrollPos = value;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void ScrollBar::setScrollPosCallback(const std::function<void(int)>& value)
    {
        _p->scrollPosCallback = value;
    }

    void ScrollBar::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        FTK_P();

        if (!p.size.displayScale.has_value() ||
            (p.size.displayScale.has_value() && p.size.displayScale.value() != event.displayScale))
        {
            p.size.displayScale = event.displayScale;
            p.size.handle = event.style->getSizeRole(SizeRole::Handle, event.displayScale);
            p.size.border = event.style->getSizeRole(SizeRole::Border, event.displayScale);
        }

        Size2I sizeHint(p.size.handle, p.size.handle);
        switch (p.orientation)
        {
        case Orientation::Horizontal:
            sizeHint.w += p.size.handle;
            break;
        case Orientation::Vertical:
            sizeHint.h += p.size.handle;
            break;
        default: break;
        }
        _setSizeHint(sizeHint);
    }

    void ScrollBar::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IWidget::drawEvent(drawRect, event);
        FTK_P();

        const int scrollPosMax = _getScrollPosMax();
        if (scrollPosMax > 0)
        {
            const Box2I g = margin(_getHandleGeometry(), -p.size.border);
            event.render->drawRect(
                g,
                event.style->getColorRole(ColorRole::Button));

            if (_isMousePressed())
            {
                event.render->drawRect(
                    g,
                    event.style->getColorRole(ColorRole::Pressed));
            }
            else if (_isMouseInside())
            {
                event.render->drawRect(
                    g,
                    event.style->getColorRole(ColorRole::Hover));
            }
        }
    }

    void ScrollBar::mouseEnterEvent(MouseEnterEvent& event)
    {
        IWidget::mouseEnterEvent(event);
        _setDrawUpdate();
    }

    void ScrollBar::mouseLeaveEvent()
    {
        IWidget::mouseLeaveEvent();
        _setDrawUpdate();
    }

    void ScrollBar::mouseMoveEvent(MouseMoveEvent& event)
    {
        IWidget::mouseMoveEvent(event);
        FTK_P();
        if (_isMousePressed())
        {
            int scrollPos = 0;
            const float s = _getScrollScale();
            switch (p.orientation)
            {
            case Orientation::Horizontal:
                scrollPos = p.mouse.pressedScrollPos +
                    (event.pos.x - _getMousePressPos().x) * s;
                break;
            case Orientation::Vertical:
                scrollPos = p.mouse.pressedScrollPos +
                    (event.pos.y - _getMousePressPos().y) * s;
                break;
            default: break;
            }
            const int scrollPosMax = _getScrollPosMax();
            const int scrollPosClamped = clamp(scrollPos, 0, scrollPosMax);
            if (scrollPosClamped != p.scrollPos)
            {
                p.scrollPos = scrollPosClamped;
                _setSizeUpdate();
                _setDrawUpdate();
                if (p.scrollPosCallback)
                {
                    p.scrollPosCallback(p.scrollPos);
                }
            }
        }
    }

    void ScrollBar::mousePressEvent(MouseClickEvent& event)
    {
        IWidget::mousePressEvent(event);
        FTK_P();
        const Box2I& g = getGeometry();
        const Box2I hg = _getHandleGeometry();
        if (!contains(hg, event.pos))
        {
            int scrollPos = 0;
            const float s = _getScrollScale();
            switch (p.orientation)
            {
            case Orientation::Horizontal:
                scrollPos = (event.pos.x - hg.w() / 2 - g.min.x) * s;
                break;
            case Orientation::Vertical:
                scrollPos = (event.pos.y - hg.h() / 2 - g.min.y) * s;
                break;
            default: break;
            }
            const int scrollPosMax = _getScrollPosMax();
            const int scrollPosClamped = clamp(scrollPos, 0, scrollPosMax);
            if (scrollPosClamped != p.scrollPos)
            {
                p.scrollPos = scrollPosClamped;
                _setSizeUpdate();
                _setDrawUpdate();
                if (p.scrollPosCallback)
                {
                    p.scrollPosCallback(p.scrollPos);
                }
            }
        }
        p.mouse.pressedScrollPos = p.scrollPos;
        _setDrawUpdate();
    }

    void ScrollBar::mouseReleaseEvent(MouseClickEvent& event)
    {
        IWidget::mouseReleaseEvent(event);
        _setDrawUpdate();
    }

    Box2I ScrollBar::_getHandleGeometry() const
    {
        FTK_P();
        Box2I out;
        const Box2I& g = getGeometry();
        switch (p.orientation)
        {
        case Orientation::Horizontal:
        {
            const int w = p.scrollSize - g.w();
            const int w2 = std::max(
                static_cast<int>(g.w() / static_cast<float>(p.scrollSize) * g.w()),
                p.size.handle * 2);
            const int x = p.scrollPos / static_cast<float>(w) * (g.w() - w2);
            out = Box2I(
                g.x() + x,
                g.y(),
                w2,
                g.h());
            break;
        }
        case Orientation::Vertical:
        {
            const int h = p.scrollSize - g.h();
            const int h2 = std::max(
                static_cast<int>(g.h() / static_cast<float>(p.scrollSize) * g.h()),
                p.size.handle * 2);
            const int y = p.scrollPos / static_cast<float>(h) * (g.h() - h2);
            out = Box2I(
                g.x(),
                g.y() + y,
                g.w(),
                h2);
            break;
        }
        default: break;
        }
        return out;
    }

    int ScrollBar::_getScrollPosMax() const
    {
        FTK_P();
        int out = 0;
        const Box2I& g = getGeometry();
        switch (p.orientation)
        {
        case Orientation::Horizontal:
            out = std::max(0, p.scrollSize - g.w());
            break;
        case Orientation::Vertical:
            out = std::max(0, p.scrollSize - g.h());
            break;
        default: break;
        }
        return out;
    }

    float ScrollBar::_getScrollScale() const
    {
        FTK_P();
        float out = 0.F;
        const Box2I& g = getGeometry();
        switch (p.orientation)
        {
        case Orientation::Horizontal:
            out = g.w() > 0 ? (p.scrollSize / static_cast<float>(g.w())) : 0.F;
            break;
        case Orientation::Vertical:
            out = g.h() > 0 ? (p.scrollSize / static_cast<float>(g.h())) : 0.F;
            break;
        default: break;
        }
        return out;
    }
}