// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "ColorWidgets.h"

#include <ftk/Ui/ColorWidget.h>

void ColorWidgets::_init(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<IWidget>& parent)
{
    IWidget::_init(context, "ColorWidgets", parent);
    
    _layout = HorizontalLayout::create(context, shared_from_this());
    _layout->setMarginRole(SizeRole::Margin);

    auto colorWidget = ColorWidget::create(context, _layout);
    colorWidget->setColor(Color4F(1.F, .6F, 0.F));

    colorWidget = ColorWidget::create(context, _layout);
    colorWidget->setColor(Color4F(0.F, .6F, 1.F));
    colorWidget->setMode(ColorWidgetMode::HSV);
}

ColorWidgets::~ColorWidgets()
{}

std::shared_ptr<ColorWidgets> ColorWidgets::create(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<IWidget>& parent)
{
    auto out = std::shared_ptr<ColorWidgets>(new ColorWidgets);
    out->_init(context, parent);
    return out;
}

void ColorWidgets::setGeometry(const Box2I& value)
{
    IWidget::setGeometry(value);
    _layout->setGeometry(value);
}

void ColorWidgets::sizeHintEvent(const SizeHintEvent& event)
{
    IWidget::sizeHintEvent(event);
    _setSizeHint(_layout->getSizeHint());
}
