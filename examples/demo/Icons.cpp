// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "Icons.h"

#include <feather-tk/ui/Icon.h>

void Icons::_init(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<IWidget>& parent)
{
    IWidget::_init(context, "Icons", parent);

    _layout = GridLayout::create(context, shared_from_this());
    _layout->setMarginRole(SizeRole::Margin);

    auto icon = Icon::create(context, "PlaybackReverse", _layout);
    _layout->setGridPos(icon, 0, 0);
    icon = Icon::create(context, "PlaybackStop", _layout);
    _layout->setGridPos(icon, 0, 1);
    icon = Icon::create(context, "PlaybackForward", _layout);
    _layout->setGridPos(icon, 0, 2);
    icon = Icon::create(context, "Settings", _layout);
    _layout->setGridPos(icon, 0, 3);

    icon = Icon::create(context, "FrameStart", _layout);
    _layout->setGridPos(icon, 1, 0);
    icon = Icon::create(context, "FramePrev", _layout);
    _layout->setGridPos(icon, 1, 1);
    icon = Icon::create(context, "FrameNext", _layout);
    _layout->setGridPos(icon, 1, 2);
    icon = Icon::create(context, "FrameEnd", _layout);
    _layout->setGridPos(icon, 1, 3);

    icon = Icon::create(context, "FileOpen", _layout);
    _layout->setGridPos(icon, 2, 0);
    icon = Icon::create(context, "FileClose", _layout);
    _layout->setGridPos(icon, 2, 1);
    icon = Icon::create(context, "FileCloseAll", _layout);
    _layout->setGridPos(icon, 2, 2);
    icon = Icon::create(context, "FileReload", _layout);
    _layout->setGridPos(icon, 2, 3);

    icon = Icon::create(context, "ViewFrame", _layout);
    _layout->setGridPos(icon, 3, 0);
    icon = Icon::create(context, "ViewZoomIn", _layout);
    _layout->setGridPos(icon, 3, 1);
    icon = Icon::create(context, "ViewZoomOut", _layout);
    _layout->setGridPos(icon, 3, 2);
    icon = Icon::create(context, "ViewZoomReset", _layout);
    _layout->setGridPos(icon, 3, 3);
}

Icons::~Icons()
{}

std::shared_ptr<Icons> Icons::create(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<IWidget>& parent)
{
    auto out = std::shared_ptr<Icons>(new Icons);
    out->_init(context, parent);
    return out;
}

void Icons::setGeometry(const Box2I& value)
{
    IWidget::setGeometry(value);
    _layout->setGeometry(value);
}

void Icons::sizeHintEvent(const SizeHintEvent& event)
{
    IWidget::sizeHintEvent(event);
    _setSizeHint(_layout->getSizeHint());
}
