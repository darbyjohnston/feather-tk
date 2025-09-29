// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "Popups.h"

#include <ftk/Ui/ComboBox.h>
#include <ftk/Ui/ColorSwatch.h>

void Popups::_init(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<IWidget>& parent)
{
    IWidget::_init(context, "Popups", parent);
    
    _layout = FormLayout::create(context, shared_from_this());
    _layout->setMarginRole(SizeRole::Margin);

    auto comboBox = ComboBox::create(context);
    comboBox->setItems({ "One", "Two", "Three" });
    _layout->addRow("Combo box: ", comboBox);

    auto colorSwatch = ColorSwatch::create(context);
    colorSwatch->setColor(Color4F(1.F, .6F, 0.F));
    colorSwatch->setEditable(true);
    _layout->addRow("Swatch:", colorSwatch);
}

Popups::~Popups()
{}

std::shared_ptr<Popups> Popups::create(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<IWidget>& parent)
{
    auto out = std::shared_ptr<Popups>(new Popups);
    out->_init(context, parent);
    return out;
}

void Popups::setGeometry(const Box2I& value)
{
    IWidget::setGeometry(value);
    _layout->setGeometry(value);
}

void Popups::sizeHintEvent(const SizeHintEvent& event)
{
    IWidget::sizeHintEvent(event);
    _setSizeHint(_layout->getSizeHint());
}
