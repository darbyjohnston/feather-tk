// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/UI/TextEditPrivate.h>

#include <ftk/UI/App.h>
#include <ftk/UI/DrawUtil.h>
#include <ftk/UI/IWindow.h>
#include <ftk/UI/LayoutUtil.h>

#include <ftk/Core/Format.h>
#include <ftk/Core/RenderUtil.h>

#include <optional>

namespace ftk
{
    struct TextEditLineWidget::Private
    {
        TextEditOptions options;
        std::shared_ptr<TextEditModel> model;

        struct SizeData
        {
            std::optional<float> displayScale;
            int margin = 0;
            FontInfo fontInfo;
            FontMetrics fontMetrics;
            std::optional<Size2I> textSize;
        };
        SizeData size;

        std::shared_ptr<ListObserver<std::string> > textObserver;
    };

    void TextEditLineWidget::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<TextEditModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "ftk::TextEditLineWidget", parent);
        FTK_P();

        p.model = model;
        
        p.textObserver = ListObserver<std::string>::create(
            p.model->observeText(),
            [this](const std::vector<std::string>& value)
            {
                FTK_P();
                p.size.textSize.reset();
                _setSizeUpdate();
                _setDrawUpdate();
            });
    }

    TextEditLineWidget::TextEditLineWidget() :
        _p(new Private)
    {}

    TextEditLineWidget::~TextEditLineWidget()
    {}

    std::shared_ptr<TextEditLineWidget> TextEditLineWidget::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<TextEditModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<TextEditLineWidget>(new TextEditLineWidget);
        out->_init(context, model, parent);
        return out;
    }

    void TextEditLineWidget::setOptions(const TextEditOptions& value)
    {
        FTK_P();
        if (value == p.options)
            return;
        p.options = value;
        p.size.displayScale.reset();
        p.size.textSize.reset();
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void TextEditLineWidget::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        FTK_P();

        if (!p.size.displayScale.has_value() ||
            (p.size.displayScale.has_value() && p.size.displayScale != event.displayScale))
        {
            p.size = Private::SizeData();
            p.size.displayScale = event.displayScale;
            p.size.margin = event.style->getSizeRole(SizeRole::MarginInside, event.displayScale);
            p.size.fontInfo = p.options.fontInfo;
            p.size.fontInfo.size *= event.displayScale;
            p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
        }

        if (!p.size.textSize.has_value())
        {
            p.size.textSize = Size2I();
            const auto& text = p.model->getText();
            for (size_t i = 0; i < text.size(); ++i)
            {
                const std::string text = Format("{0}").arg(static_cast<int>(i + 1));
                p.size.textSize->w = std::max(
                    event.fontSystem->getSize(text, p.size.fontInfo).w,
                    p.size.textSize->w);
                p.size.textSize->h += p.size.fontMetrics.lineHeight;
            }
        }

        _setSizeHint(margin(p.size.textSize.value(), p.size.margin, 0));
    }

    void TextEditLineWidget::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IWidget::drawEvent(drawRect, event);
        FTK_P();

        const Box2I& g = getGeometry();

        // Draw the line numbers.
        const auto& text = p.model->getText();
        const bool enabled = isEnabled();
        const Color4F textColor = event.style->getColorRole(enabled ?
            ColorRole::Text :
            ColorRole::TextDisabled);
        for (size_t i = 0; i < text.size(); ++i)
        {
            const Box2I textBox(
                g.min.x + p.size.margin,
                g.min.y + p.size.fontMetrics.lineHeight * i,
                p.size.textSize->w + p.size.margin * 2,
                p.size.fontMetrics.lineHeight);
            if (intersects(textBox, drawRect))
            {
                const std::string text = Format("{0}").arg(static_cast<int>(i + 1));
                event.render->drawText(
                    event.fontSystem->getGlyphs(text, p.size.fontInfo),
                    p.size.fontMetrics,
                    textBox.min,
                    textColor);
            }
        }
    }
}