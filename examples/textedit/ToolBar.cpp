// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "ToolBar.h"

#include "Actions.h"

#include <ftk/UI/Divider.h>
#include <ftk/UI/ToolBar.h>

using namespace ftk;

namespace examples
{
    namespace textedit
    {
        void ToolBar::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<Actions>& actions,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "examples::textedit::ToolBar", parent);

            _layout = HorizontalLayout::create(context, shared_from_this());
            _layout->setSpacingRole(SizeRole::SpacingSmall);

            auto fileToolBar = ftk::ToolBar::create(context, Orientation::Horizontal, _layout);
            for (const auto& key :
                { "File/New", "File/Open", "File/Close", "File/CloseAll" })
            {
                fileToolBar->addAction(actions->getAction(key));
            }

            Divider::create(context, Orientation::Horizontal, _layout);

            auto editToolBar = ftk::ToolBar::create(context, Orientation::Horizontal, _layout);
            for (const auto& key :
                { "Edit/Settings" })
            {
                editToolBar->addAction(actions->getAction(key));
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
            IWidget::sizeHintEvent(event);
            _setSizeHint(_layout->getSizeHint());
        }
    }
}