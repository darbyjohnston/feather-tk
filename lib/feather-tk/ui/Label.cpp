// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/Label.h>

#include <feather-tk/ui/LayoutUtil.h>

#include <feather-tk/core/String.h>

#include <optional>

namespace feather_tk
{
    struct Label::Private
    {
        std::string text;
        ColorRole textRole = ColorRole::Text;
        SizeRole hMarginRole = SizeRole::None;
        SizeRole vMarginRole = SizeRole::None;
        FontRole fontRole = FontRole::Label;
        FontInfo fontInfo;

        struct SizeData
        {
            std::optional<float> displayScale;
            int hMargin = 0;
            int vMargin = 0;
            FontInfo fontInfo;
            FontMetrics fontMetrics;
            Size2I textSize;
        };
        SizeData size;

        struct DrawData
        {
            Box2I g;
            Box2I g2;
            std::vector<std::shared_ptr<Glyph> > glyphs;
        };
        std::optional<DrawData> draw;
    };

    void Label::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "feather_tk::Label", parent);
        setHAlign(HAlign::Left);
        setVAlign(VAlign::Center);
    }

    Label::Label() :
        _p(new Private)
    {}

    Label::~Label()
    {}

    std::shared_ptr<Label> Label::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<Label>(new Label);
        out->_init(context, parent);
        return out;
    }

    std::shared_ptr<Label> Label::create(
        const std::shared_ptr<Context>& context,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = create(context, parent);
        out->setText(text);
        return out;
    }

    const std::string& Label::getText() const
    {
        return _p->text;
    }

    void Label::setText(const std::string& value)
    {
        FEATHER_TK_P();
        if (value == p.text)
            return;
        p.text = value;
        p.size.displayScale.reset();
        _setSizeUpdate();
        _setDrawUpdate();
    }

    ColorRole Label::getTextRole() const
    {
        return _p->textRole;
    }

    void Label::setTextRole(ColorRole value)
    {
        FEATHER_TK_P();
        if (value == p.textRole)
            return;
        p.textRole = value;
        _setDrawUpdate();
    }

    SizeRole Label::getMarginRole() const
    {
        return _p->hMarginRole;
    }

    SizeRole Label::getHMarginRole() const
    {
        return _p->hMarginRole;
    }

    SizeRole Label::getVMarginRole() const
    {
        return _p->vMarginRole;
    }

    void Label::setMarginRole(SizeRole value)
    {
        FEATHER_TK_P();
        if (value == p.hMarginRole && value == p.vMarginRole)
            return;
        p.hMarginRole = value;
        p.vMarginRole = value;
        p.size.displayScale.reset();
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void Label::setMarginRole(SizeRole horizontal, SizeRole vertical)
    {
        FEATHER_TK_P();
        if (horizontal == p.hMarginRole && vertical == p.vMarginRole)
            return;
        p.hMarginRole = horizontal;
        p.vMarginRole = vertical;
        p.size.displayScale.reset();
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void Label::setHMarginRole(SizeRole value)
    {
        FEATHER_TK_P();
        if (value == p.hMarginRole)
            return;
        p.hMarginRole = value;
        p.size.displayScale.reset();
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void Label::setVMarginRole(SizeRole value)
    {
        FEATHER_TK_P();
        if (value == p.vMarginRole)
            return;
        p.vMarginRole = value;
        p.size.displayScale.reset();
        _setSizeUpdate();
        _setDrawUpdate();
    }

    FontRole Label::getFontRole() const
    {
        return _p->fontRole;
    }

    void Label::setFontRole(FontRole value)
    {
        FEATHER_TK_P();
        if (value == p.fontRole)
            return;
        p.fontRole = value;
        p.size.displayScale.reset();
        _setSizeUpdate();
        _setDrawUpdate();
    }

    const FontInfo& Label::getFontInfo() const
    {
        return _p->fontInfo;
    }

    void Label::setFontInfo(const FontInfo& value)
    {
        FEATHER_TK_P();
        if (value == p.fontInfo)
            return;
        p.fontRole = FontRole::None;
        p.fontInfo = value;
        p.size.displayScale.reset();
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void Label::setGeometry(const Box2I& value)
    {
        const bool changed = value != getGeometry();
        IWidget::setGeometry(value);
        FEATHER_TK_P();
        if (changed)
        {
            p.draw.reset();
        }
    }

    void Label::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        FEATHER_TK_P();

        if (!p.size.displayScale.has_value() ||
            (p.size.displayScale.has_value() && p.size.displayScale.value() != event.displayScale))
        {
            p.size.displayScale = event.displayScale;
            p.size.hMargin = event.style->getSizeRole(p.hMarginRole, event.displayScale);
            p.size.vMargin = event.style->getSizeRole(p.vMarginRole, event.displayScale);
            if (p.fontRole != FontRole::None)
            {
                p.size.fontInfo = event.style->getFontRole(p.fontRole, event.displayScale);
            }
            else
            {
                p.size.fontInfo = p.fontInfo;
                p.size.fontInfo.size *= event.displayScale;
            }
            p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
            p.size.textSize = event.fontSystem->getSize(p.text, p.size.fontInfo);
            p.draw.reset();
        }

        Size2I sizeHint(p.size.textSize);
        sizeHint = margin(sizeHint, p.size.hMargin, p.size.vMargin);
        _setSizeHint(sizeHint);
    }

    void Label::clipEvent(const Box2I& clipRect, bool clipped)
    {
        IWidget::clipEvent(clipRect, clipped);
        FEATHER_TK_P();
        if (clipped)
        {
            p.draw.reset();
        }
    }

    void Label::drawEvent(const Box2I& drawRect, const DrawEvent& event)
    {
        IWidget::drawEvent(drawRect, event);
        FEATHER_TK_P();

        if (!p.draw.has_value())
        {
            p.draw = Private::DrawData();
            p.draw->g = align(getGeometry(), getSizeHint(), getHAlign(), getVAlign());
            p.draw->g2 = margin(p.draw->g, -p.size.hMargin, -p.size.vMargin, -p.size.hMargin, -p.size.vMargin);
        }

        if (!p.text.empty() && p.draw->glyphs.empty())
        {
            p.draw->glyphs = event.fontSystem->getGlyphs(p.text, p.size.fontInfo);
        }
        event.render->drawText(
            p.draw->glyphs,
            p.size.fontMetrics,
            p.draw->g2.min,
            event.style->getColorRole(isEnabled() ?
                p.textRole :
                ColorRole::TextDisabled));
    }
}