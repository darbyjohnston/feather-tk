// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "Images.h"

#include <ftk/UI/ImageWidget.h>
#include <ftk/UI/RowLayout.h>
#include <ftk/UI/SVGWidget.h>

#include <ftk/Core/ImageIO.h>

using namespace ftk;

namespace ftk_resource
{
    extern std::vector<uint8_t> Charlie;
    extern std::vector<uint8_t> TestDrawing;
}

namespace widgets
{
    void Images::_init(const std::shared_ptr<Context>& context)
    {
        ftk::IWidget::_init(context, "Images", nullptr);

        // Create a layout.
        auto layout = VerticalLayout::create(context);
        layout->setMarginRole(SizeRole::Margin);
        _scrollWidget = ScrollWidget::create(context, ScrollType::Both, shared_from_this());
        _scrollWidget->setBorder(false);
        _scrollWidget->setWidget(layout);

        // Create image widget.
        auto imageWidget = ImageWidget::create(context, layout);
        auto imageIO = context->getSystem<ImageIO>();
        InMemoryFile memory(ftk_resource::Charlie.data(), ftk_resource::Charlie.size());
        if (auto read = imageIO->read("Charlie.png", memory))
        {
            imageWidget->setImage(read->read());
        }

        // Create SVG widget.
        auto svgWidget = SvgWidget::create(context, layout);
        svgWidget->setSVGData(ftk_resource::TestDrawing);
        svgWidget->setSVGWidth(300);
    }

    Images::~Images()
    {}

    std::shared_ptr<Images> Images::create(const std::shared_ptr<Context>& context)
    {
        auto out = std::shared_ptr<Images>(new Images);
        out->_init(context);
        return out;
    }

    void Images::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _scrollWidget->setGeometry(value);
    }

    void Images::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        _setSizeHint(_scrollWidget->getSizeHint());
    }
}
