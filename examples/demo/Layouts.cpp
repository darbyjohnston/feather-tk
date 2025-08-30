// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "Layouts.h"

#include <ftk/ui/GridLayout.h>
#include <ftk/ui/Label.h>
#include <ftk/ui/RowLayout.h>

void Layouts::_init(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<IWidget>& parent)
{
    IWidget::_init(context, "Layouts", parent);
    
    _layout = FormLayout::create(context, shared_from_this());
    _layout->setMarginRole(SizeRole::Margin);

    auto hLayout = HorizontalLayout::create(context);
    hLayout->setSpacingRole(SizeRole::SpacingSmall);
    Label::create(context, "1", hLayout);
    Label::create(context, "2", hLayout);
    Label::create(context, "3", hLayout);
    _layout->addRow("Horizontal:", hLayout);

    auto vLayout = VerticalLayout::create(context);
    vLayout->setSpacingRole(SizeRole::SpacingSmall);
    Label::create(context, "1", vLayout);
    Label::create(context, "2", vLayout);
    Label::create(context, "3", vLayout);
    _layout->addRow("Vertical:", vLayout);

    auto gridLayout = GridLayout::create(context);
    gridLayout->setSpacingRole(SizeRole::SpacingSmall);
    gridLayout->setGridPos(Label::create(context, "1", gridLayout), 0, 0);
    gridLayout->setGridPos(Label::create(context, "2", gridLayout), 0, 2);
    gridLayout->setGridPos(Label::create(context, "3", gridLayout), 1, 1);
    gridLayout->setGridPos(Label::create(context, "4", gridLayout), 2, 0);
    gridLayout->setGridPos(Label::create(context, "5", gridLayout), 2, 2);
    _layout->addRow("Grid:", gridLayout);
}

Layouts::~Layouts()
{}

std::shared_ptr<Layouts> Layouts::create(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<IWidget>& parent)
{
    auto out = std::shared_ptr<Layouts>(new Layouts);
    out->_init(context, parent);
    return out;
}

void Layouts::setGeometry(const Box2I& value)
{
    IWidget::setGeometry(value);
    _layout->setGeometry(value);
}

void Layouts::sizeHintEvent(const SizeHintEvent& event)
{
    IWidget::sizeHintEvent(event);
    _setSizeHint(_layout->getSizeHint());
}
