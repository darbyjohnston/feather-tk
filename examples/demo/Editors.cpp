// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "Editors.h"

#include <ftk/UI/DoubleEdit.h>
#include <ftk/UI/FloatEdit.h>
#include <ftk/UI/IntEdit.h>
#include <ftk/UI/LineEdit.h>

void Editors::_init(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<IWidget>& parent)
{
    IWidget::_init(context, "Editors", parent);
    
    _layout = FormLayout::create(context, shared_from_this());
    _layout->setMarginRole(SizeRole::Margin);

    auto lineEdit = LineEdit::create(context);
    lineEdit->setText("Text");
    _layout->addRow("Line edit:", lineEdit);

    auto intEdit = IntEdit::create(context);
    intEdit->setValue(42);
    _layout->addRow("Integer edit:", intEdit);

    auto floatEdit = FloatEdit::create(context);
    floatEdit->setRange(0.F, 100.F);
    floatEdit->setValue(42.F);
    _layout->addRow("Float edit:", floatEdit);

    auto doubleEdit = DoubleEdit::create(context);
    doubleEdit->setRange(0.F, 100.F);
    doubleEdit->setValue(11.11);
    _layout->addRow("Double edit:", doubleEdit);
}

Editors::~Editors()
{}

std::shared_ptr<Editors> Editors::create(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<IWidget>& parent)
{
    auto out = std::shared_ptr<Editors>(new Editors);
    out->_init(context, parent);
    return out;
}

void Editors::setGeometry(const Box2I& value)
{
    IWidget::setGeometry(value);
    _layout->setGeometry(value);
}

void Editors::sizeHintEvent(const SizeHintEvent& event)
{
    IWidget::sizeHintEvent(event);
    _setSizeHint(_layout->getSizeHint());
}
