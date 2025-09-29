// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "Sliders.h"

#include <ftk/Ui/DoubleEditSlider.h>
#include <ftk/Ui/FloatEditSlider.h>
#include <ftk/Ui/IntEditSlider.h>

void Sliders::_init(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<IWidget>& parent)
{
    IWidget::_init(context, "Sliders", parent);
    
    _layout = FormLayout::create(context, shared_from_this());
    _layout->setMarginRole(SizeRole::Margin);

    auto intSlider = IntEditSlider::create(context);
    intSlider->setValue(42);
    _layout->addRow("Integer slider:", intSlider);

    auto floatSlider = FloatEditSlider::create(context);
    floatSlider->setRange(0.F, 100.F);
    floatSlider->setValue(42.F);
    _layout->addRow("Float slider:", floatSlider);

    auto doubleSlider = DoubleEditSlider::create(context);
    doubleSlider->setRange(0.F, 100.F);
    doubleSlider->setValue(11.11);
    _layout->addRow("Double slider:", doubleSlider);
}

Sliders::~Sliders()
{}

std::shared_ptr<Sliders> Sliders::create(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<IWidget>& parent)
{
    auto out = std::shared_ptr<Sliders>(new Sliders);
    out->_init(context, parent);
    return out;
}

void Sliders::setGeometry(const Box2I& value)
{
    IWidget::setGeometry(value);
    _layout->setGeometry(value);
}

void Sliders::sizeHintEvent(const SizeHintEvent& event)
{
    IWidget::sizeHintEvent(event);
    _setSizeHint(_layout->getSizeHint());
}
