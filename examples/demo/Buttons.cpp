// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "Buttons.h"

#include <ftk/UI/CheckBox.h>
#include <ftk/UI/GridLayout.h>
#include <ftk/UI/GroupBox.h>
#include <ftk/UI/PushButton.h>
#include <ftk/UI/RadioButton.h>
#include <ftk/UI/ToolButton.h>

void Buttons::_init(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<IWidget>& parent)
{
    IWidget::_init(context, "Buttons", parent);

    _layout = FormLayout::create(context, shared_from_this());
    _layout->setMarginRole(SizeRole::Margin);

    _layout->addRow("Push button:", PushButton::create(context, "Push"));

    auto toolButton = ToolButton::create(context);
    toolButton->setIcon("Settings");
    _layout->addRow("Tool button:", toolButton);

    auto checkBox = CheckBox::create(context, "Check");
    checkBox->setChecked(true);
    _layout->addRow("Check box:", checkBox);

    auto radioButton = RadioButton::create(context, "Radio");
    radioButton->setChecked(true);
    _layout->addRow("Radio button:", radioButton);
}

Buttons::~Buttons()
{}

std::shared_ptr<Buttons> Buttons::create(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<IWidget>& parent)
{
    auto out = std::shared_ptr<Buttons>(new Buttons);
    out->_init(context, parent);
    return out;
}

void Buttons::setGeometry(const Box2I& value)
{
    IWidget::setGeometry(value);
    _layout->setGeometry(value);
}

void Buttons::sizeHintEvent(const SizeHintEvent& event)
{
    IWidget::sizeHintEvent(event);
    _setSizeHint(_layout->getSizeHint());
}
