// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/UI/IMouseWidget.h>

#include <ftk/UI/IWindow.h>

#include <ftk/Core/String.h>

namespace ftk
{
    void IMouseWidget::_init(
        const std::shared_ptr<Context>& context,
        const std::string& objectName,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, objectName, parent);
    }

    IMouseWidget::~IMouseWidget()
    {}

    void IMouseWidget::mouseEnterEvent(MouseEnterEvent& event)
    {
        if (_mouseHoverEnabled)
        {
            event.accept = true;
        }
        _mouseInside = true;
        _mousePos = event.pos;
    }

    void IMouseWidget::mouseLeaveEvent()
    {
        _mouseInside = false;
    }

    void IMouseWidget::mouseMoveEvent(MouseMoveEvent& event)
    {
        if (_mouseHoverEnabled)
        {
            event.accept = true;
        }
        _mousePos = event.pos;
    }

    void IMouseWidget::mousePressEvent(MouseClickEvent& event)
    {
        const bool button =
            _mousePressButton != 0 ?
            event.button == _mousePressButton :
            true;
        const bool modifiers =
            _mousePressModifiers != -1 ?
            event.modifiers == _mousePressModifiers :
            true;
        if (_mousePressEnabled && button && modifiers)
        {
            event.accept = true;
            _mousePos = event.pos;
            _mousePress = true;
            _mousePressPos = event.pos;
        }
    }

    void IMouseWidget::mouseReleaseEvent(MouseClickEvent& event)
    {
        if (_mousePress)
        {
            event.accept = true;
            _mousePress = false;
        }
    }

    void IMouseWidget::_setMouseHoverEnabled(bool value)
    {
        _mouseHoverEnabled = value;
    }

    void IMouseWidget::_setMousePressEnabled(bool value, int button, int modifiers)
    {
        _mousePressEnabled = value;
        _mousePressButton = button;
        _mousePressModifiers = modifiers;
    }

    bool IMouseWidget::_isMouseInside() const
    {
        return _mouseInside;
    }

    const V2I& IMouseWidget::_getMousePos() const
    {
        return _mousePos;
    }

    bool IMouseWidget::_isMousePressed() const
    {
        return _mousePress;
    }

    const V2I& IMouseWidget::_getMousePressPos() const
    {
        return _mousePressPos;
    }
}