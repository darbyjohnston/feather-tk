// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "StatusBar.h"

#include "App.h"
#include "DocumentModel.h"

#include <ftk/Core/Format.h>
#include <ftk/Core/String.h>

using namespace ftk;

namespace examples
{
    namespace objview
    {
        void StatusBar::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "examples::objview::StatusBar", parent);

            // Layout the widgets.
            _layout = HorizontalLayout::create(context, shared_from_this());
            _layout->setMarginRole(SizeRole::MarginInside);
            _layout->setSpacingRole(SizeRole::SpacingSmall);
            _layout->addSpacer(Stretch::Expanding);

            // Observe the current document and update the widgets.
            std::weak_ptr<App> appWeak(app);
            _currentObserver = ftk::ValueObserver<std::shared_ptr<Document> >::create(
                app->getDocumentModel()->observeCurrent(),
                [this, appWeak](const std::shared_ptr<Document>& doc)
                {
                    if (doc)
                    {
                    }
                    else
                    {
                    }
                });
        }

        StatusBar::~StatusBar()
        {}

        std::shared_ptr<StatusBar> StatusBar::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<StatusBar>(new StatusBar);
            out->_init(context, app, parent);
            return out;
        }

        void StatusBar::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            _layout->setGeometry(value);
        }

        void StatusBar::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _setSizeHint(_layout->getSizeHint());
        }
    }
}