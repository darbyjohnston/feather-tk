// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/ui/ListItemsWidgetPrivate.h>

#include <ftk/ui/DrawUtil.h>

#include <optional>

namespace ftk
{
    struct ListItemButton::Private
    {
        bool current = false;

        struct SizeData
        {
            std::optional<float> displayScale;
            int margin = 0;
            int spacing = 0;
            int borderFocus = 0;
            int pad = 0;
            FontInfo fontInfo;
            FontMetrics fontMetrics;
            Size2I textSize;
        };
        SizeData size;

        struct DrawData
        {
            Box2I g;
            Box2I g2;
            TriMesh2F borderFocus;
            std::vector<std::shared_ptr<Glyph> > glyphs;
        };
        std::optional<DrawData> draw;
    };

    void ListItemButton::_init(
        const std::shared_ptr<Context>& context,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "ftk::ListItemButton", parent);
        FTK_P();
        _setMouseHoverEnabled(true);
        _setMousePressEnabled(true);
        setText(text);
        setButtonRole(ColorRole::None);
    }

    ListItemButton::ListItemButton() :
        _p(new Private)
    {}

    ListItemButton::~ListItemButton()
    {}

    std::shared_ptr<ListItemButton> ListItemButton::create(
        const std::shared_ptr<Context>& context,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<ListItemButton>(new ListItemButton);
        out->_init(context, text, parent);
        return out;
    }

    void ListItemButton::setCurrent(bool value)
    {
        FTK_P();
        if (p.current == value)
            return;
        p.current = value;
        _setDrawUpdate();
    }

    void ListItemButton::setGeometry(const Box2I& value)
    {
        const bool changed = value != getGeometry();
        IButton::setGeometry(value);
        FTK_P();
        if (changed)
        {
            p.draw.reset();
        }
    }

    void ListItemButton::sizeHintEvent(const SizeHintEvent& event)
    {
        IButton::sizeHintEvent(event);
        FTK_P();

        if (!p.size.displayScale.has_value() ||
            (p.size.displayScale.has_value() && p.size.displayScale.value() != event.displayScale))
        {
            p.size.displayScale = event.displayScale;
            p.size.margin = event.style->getSizeRole(SizeRole::MarginInside, event.displayScale);
            p.size.spacing = event.style->getSizeRole(SizeRole::SpacingSmall, event.displayScale);
            p.size.borderFocus = event.style->getSizeRole(SizeRole::BorderFocus, event.displayScale);
            p.size.pad = event.style->getSizeRole(SizeRole::LabelPad, event.displayScale);
            p.size.fontInfo = event.style->getFontRole(FontRole::Label, event.displayScale);
            p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
            p.size.textSize = event.fontSystem->getSize(_text, p.size.fontInfo);
            p.draw.reset();
        }

        Size2I sizeHint(
            p.size.textSize.w + p.size.pad * 2,
            p.size.fontMetrics.lineHeight);
        sizeHint = margin(sizeHint, p.size.margin + p.size.borderFocus);
        _setSizeHint(sizeHint);
    }

    void ListItemButton::clipEvent(const Box2I& clipRect, bool clipped)
    {
        IButton::clipEvent(clipRect, clipped);
        FTK_P();
        if (clipped)
        {
            p.draw.reset();
        }
    }

    void ListItemButton::drawEvent(const Box2I& drawRect, const DrawEvent& event)
    {
        IButton::drawEvent(drawRect, event);
        FTK_P();

        if (!p.draw.has_value())
        {
            p.draw = Private::DrawData();
            p.draw->g = getGeometry();
            p.draw->g2 = margin(p.draw->g, -(p.size.margin + p.size.borderFocus));
            p.draw->borderFocus = border(p.draw->g, p.size.borderFocus);
        }

        // Draw the background.
        const ColorRole colorRole = _checked ? _checkedRole : _buttonRole;
        if (colorRole != ColorRole::None)
        {
            event.render->drawRect(
                p.draw->g,
                event.style->getColorRole(colorRole));
        }

        // Draw the current state.
        if (p.current)
        {
            event.render->drawMesh(
                p.draw->borderFocus,
                event.style->getColorRole(ColorRole::KeyFocus));
        }

        // Draw the mouse state.
        if (_isMousePressed())
        {
            event.render->drawRect(
                p.draw->g,
                event.style->getColorRole(ColorRole::Pressed));
        }
        else if (_isMouseInside())
        {
            event.render->drawRect(
                p.draw->g,
                event.style->getColorRole(ColorRole::Hover));
        }

        // Draw the text.
        if (!_text.empty() && p.draw->glyphs.empty())
        {
            p.draw->glyphs = event.fontSystem->getGlyphs(_text, p.size.fontInfo);
        }
        event.render->drawText(
            p.draw->glyphs,
            p.size.fontMetrics,
            V2I(p.draw->g2.x() + p.size.pad, p.draw->g2.y()),
            event.style->getColorRole(ColorRole::Text));
    }
}