// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/Icon.h>

#include <feather-tk/ui/LayoutUtil.h>

#include <feather-tk/core/String.h>

#include <optional>

namespace feather_tk
{
    struct Icon::Private
    {
        std::string icon;
        float iconScale = 1.F;
        std::shared_ptr<Image> iconImage;
        SizeRole marginRole = SizeRole::None;

        struct SizeData
        {
            std::optional<float> displayScale;
            int margin = 0;
        };
        SizeData size;
    };

    void Icon::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "feather_tk::Icon", parent);
        setHAlign(HAlign::Left);
        setVAlign(VAlign::Center);
    }

    Icon::Icon() :
        _p(new Private)
    {}

    Icon::~Icon()
    {}

    std::shared_ptr<Icon> Icon::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<Icon>(new Icon);
        out->_init(context, parent);
        return out;
    }

    std::shared_ptr<Icon> Icon::create(
        const std::shared_ptr<Context>& context,
        const std::string& icon,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = create(context, parent);
        out->setIcon(icon);
        return out;
    }

    const std::string& Icon::getIcon() const
    {
        return _p->icon;
    }

    void Icon::setIcon(const std::string& value)
    {
        FEATHER_TK_P();
        if (value == p.icon)
            return;
        p.icon = value;
        p.iconImage.reset();
        _setSizeUpdate();
        _setDrawUpdate();
    }

    SizeRole Icon::getMarginRole() const
    {
        return _p->marginRole;
    }

    void Icon::setMarginRole(SizeRole value)
    {
        FEATHER_TK_P();
        if (value == p.marginRole)
            return;
        p.marginRole = value;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void Icon::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        FEATHER_TK_P();

        if (!p.size.displayScale.has_value() ||
            (p.size.displayScale.has_value() && p.size.displayScale.value() != event.displayScale))
        {
            p.size.displayScale = event.displayScale;
            p.size.margin = event.style->getSizeRole(p.marginRole, event.displayScale);
        }

        if (event.displayScale != p.iconScale)
        {
            p.iconScale = event.displayScale;
            p.iconImage.reset();
        }
        if (!p.icon.empty() && !p.iconImage)
        {
            p.iconImage = event.iconSystem->get(p.icon, event.displayScale);
        }

        Size2I sizeHint;
        if (p.iconImage)
        {
            sizeHint.w = p.iconImage->getWidth();
            sizeHint.h = p.iconImage->getHeight();
        }
        _setSizeHint(sizeHint);
    }

    void Icon::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IWidget::drawEvent(drawRect, event);
        FEATHER_TK_P();
        if (p.iconImage)
        {
            const Box2I g = margin(getGeometry(), -p.size.margin);
            const Size2I& iconSize = p.iconImage->getSize();
            event.render->drawImage(
                p.iconImage,
                Box2I(
                    g.x() + g.w() / 2 - iconSize.w / 2,
                    g.y() + g.h() / 2 - iconSize.h / 2,
                    iconSize.w,
                    iconSize.h),
                event.style->getColorRole(isEnabled() ?
                    ColorRole::Text :
                    ColorRole::TextDisabled));
        }
    }
}
