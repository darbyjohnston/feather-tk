// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "ImageWidgets.h"

#include <ftk/UI/ImageWidget.h>
#include <ftk/UI/SVGWidget.h>

#include <ftk/Core/ImageIO.h>

namespace ftk_resource
{
    extern std::vector<uint8_t> Charlie;
    extern std::vector<uint8_t> TestDrawing;
}

void ImageWidgets::_init(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<IWidget>& parent)
{
    IWidget::_init(context, "ImageWidgets", parent);
    
    _layout = HorizontalLayout::create(context, shared_from_this());
    _layout->setMarginRole(SizeRole::Margin);

    auto imageWidget = ImageWidget::create(context, _layout);
    auto imageIO = context->getSystem<ImageIO>();
    InMemoryFile memory(ftk_resource::Charlie.data(), ftk_resource::Charlie.size());
    if (auto read = imageIO->read("Charlie.png", memory))
    {
        imageWidget->setImage(read->read());
    }

    auto svgWidget = SvgWidget::create(context, _layout);
    svgWidget->setSVGData(ftk_resource::TestDrawing);
    svgWidget->setSVGWidth(300);
}

ImageWidgets::~ImageWidgets()
{}

std::shared_ptr<ImageWidgets> ImageWidgets::create(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<IWidget>& parent)
{
    auto out = std::shared_ptr<ImageWidgets>(new ImageWidgets);
    out->_init(context, parent);
    return out;
}

void ImageWidgets::setGeometry(const Box2I& value)
{
    IWidget::setGeometry(value);
    _layout->setGeometry(value);
}

void ImageWidgets::sizeHintEvent(const SizeHintEvent& event)
{
    IWidget::sizeHintEvent(event);
    _setSizeHint(_layout->getSizeHint());
}
