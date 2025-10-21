// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "ToolBar.h"

#include "Actions.h"

#include <ftk/UI/Divider.h>
#include <ftk/UI/ToolBar.h>

using namespace ftk;

namespace imageview
{
    void ToolBar::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<Actions>& actions,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "examples::imageview::ToolBar", parent);

        // Create the layout.
        _layout = HorizontalLayout::create(context, shared_from_this());
        _layout->setSpacingRole(SizeRole::SpacingSmall);

        // Create the file tool bar.
        auto fileToolBar = ftk::ToolBar::create(context, Orientation::Horizontal, _layout);
        for (const auto& key :
            { "File/Open", "File/Close", "File/CloseAll" })
        {
            fileToolBar->addAction(actions->getAction(key));
        }
        Divider::create(context, Orientation::Horizontal, _layout);

        // Create the window tool bar.
        auto windowToolBar = ftk::ToolBar::create(context, Orientation::Horizontal, _layout);
        for (const auto& key :
            { "Window/FullScreen" })
        {
            windowToolBar->addAction(actions->getAction(key));
        }
        Divider::create(context, Orientation::Horizontal, _layout);

        // Create the view tool bar.
        auto viewToolBar = ftk::ToolBar::create(context, Orientation::Horizontal, _layout);
        for (const auto& key :
            { "View/ZoomReset", "View/ZoomIn", "View/ZoomOut" })
        {
            viewToolBar->addAction(actions->getAction(key));
        }
    }

    ToolBar::~ToolBar()
    {}

    std::shared_ptr<ToolBar> ToolBar::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<Actions>& actions,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<ToolBar>(new ToolBar);
        out->_init(context, actions, parent);
        return out;
    }

    void ToolBar::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _layout->setGeometry(value);
    }

    void ToolBar::sizeHintEvent(const SizeHintEvent& event)
    {
        _setSizeHint(_layout->getSizeHint());
    }
}
