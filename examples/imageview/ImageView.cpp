// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "ImageView.h"

#include "Document.h"

using namespace ftk;

namespace imageview
{
    void ImageView::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<Document>& doc,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "examples::imageview::ImageView", parent);

        _image = doc->getImage();
    }

    ImageView::~ImageView()
    {}

    std::shared_ptr<ImageView> ImageView::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<Document>& doc,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<ImageView>(new ImageView);
        out->_init(context, doc, parent);
        return out;
    }

    void ImageView::zoomReset()
    {
        _zoom = 1.F;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void ImageView::zoomIn()
    {
        _zoom *= 2.F;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void ImageView::zoomOut()
    {
        _zoom *= .5F;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void ImageView::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        Size2I sizeHint;
        if (_image)
        {
            sizeHint = _image->getSize() * _zoom;
        }
        _setSizeHint(sizeHint);
    }

    void ImageView::drawEvent(const Box2I& drawRect, const DrawEvent& event)
    {
        IWidget::drawEvent(drawRect, event);

        const Box2I& g = getGeometry();
        event.render->drawRect(g, Color4F(0.F, 0.F, 0.F));

        if (_image)
        {
            const Size2I& size = _image->getSize() * _zoom;
            event.render->drawImage(
                _image,
                Box2I(
                    g.x() + g.w() / 2 - size.w / 2,
                    g.y() + g.h() / 2 - size.h / 2,
                    size.w,
                    size.h));
        }
    }
}
