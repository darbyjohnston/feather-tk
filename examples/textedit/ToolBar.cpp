// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "ToolBar.h"

#include "Actions.h"
#include "App.h"

#include <ftk/UI/Divider.h>

using namespace ftk;

namespace examples
{
    namespace textedit
    {
        void ToolBar::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<Actions>& actions,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "examples::textedit::ToolBar", parent);

            _actions = actions;

            _layout = HorizontalLayout::create(context, shared_from_this());
            _layout->setSpacingRole(SizeRole::SpacingSmall);

            _createFileToolBar(context, app);
            Divider::create(context, Orientation::Horizontal, _layout);
            _createEditToolBar(context, app);
        }

        ToolBar::~ToolBar()
        {}

        std::shared_ptr<ToolBar> ToolBar::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<Actions>& actions,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<ToolBar>(new ToolBar);
            out->_init(context, app, actions, parent);
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

        void ToolBar::_createFileToolBar(
            const std::shared_ptr<ftk::Context>& context,
            const std::shared_ptr<App>& app)
        {
            auto layout = HorizontalLayout::create(context, _layout);
            layout->setSpacingRole(SizeRole::None);

            for (const auto& key :
                {
                    "File/New", "File/Open", "File/Close", "File/CloseAll"
                })
            {
                _buttons[key] = ToolButton::create(
                    context,
                    _actions->getAction(key),
                    layout);
            }
        }

        void ToolBar::_createEditToolBar(
            const std::shared_ptr<ftk::Context>& context,
            const std::shared_ptr<App>& app)
        {
            auto layout = HorizontalLayout::create(context, _layout);
            layout->setSpacingRole(SizeRole::None);

            for (const auto& key :
                {
                    "Edit/Settings"
                })
            {
                _buttons[key] = ToolButton::create(
                    context,
                    _actions->getAction(key),
                    layout);
            }
        }
    }
}