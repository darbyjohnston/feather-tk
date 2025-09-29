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
    namespace textedit
    {
        void StatusBar::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "examples::textedit::StatusBar", parent);

            _label = Label::create(context);
            _label->setMarginRole(SizeRole::MarginInside);

            _layout = HorizontalLayout::create(context, shared_from_this());
            _layout->setSpacingRole(SizeRole::None);
            _layout->addSpacer(Stretch::Expanding);
            _label->setParent(_layout);

            std::weak_ptr<App> appWeak(app);
            _currentDocumentObserver = ftk::ValueObserver<int>::create(
                app->getDocumentModel()->observeCurrent(),
                [this, appWeak](int index)
                {
                    int lineCount = 0;
                    if (auto app = appWeak.lock())
                    {
                        const auto& documents = app->getDocumentModel()->getList();
                        if (index >= 0 && index < documents.size())
                        {
                            const auto& document = documents[index];
                            lineCount = document->getLines().size();
                        }
                    }
                    _label->setText(Format("Lines: {0}").arg(lineCount));
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