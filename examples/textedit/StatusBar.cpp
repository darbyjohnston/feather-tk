// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "StatusBar.h"

#include "App.h"

#include <feather-tk/core/String.h>

using namespace ftk;

namespace examples
{
    namespace textedit
    {
        void StatusBar::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "examples::textedit::StatusBar", parent);

            _label = Label::create(context, shared_from_this());
            _label->setMarginRole(SizeRole::MarginInside);

            _timer = Timer::create(context);

            _logObserver = ListObserver<LogItem>::create(
                context->getSystem<LogSystem>()->observeLogItems(),
                [this](const std::vector<LogItem>& items)
                {
                    std::string error;
                    for (const auto& item : items)
                    {
                        if (LogType::Error == item.type)
                        {
                            error = item.message;
                        }
                    }
                    if (!error.empty())
                    {
                        _label->setText("ERROR: " + error);
                        
                        _timer->start(
                            std::chrono::seconds(5),
                            [this]
                            {
                                _label->setText(std::string());
                            });
                    }
                });
        }

        StatusBar::~StatusBar()
        {}

        std::shared_ptr<StatusBar> StatusBar::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<StatusBar>(new StatusBar);
            out->_init(context, parent);
            return out;
        }

        void StatusBar::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            _label->setGeometry(value);
        }

        void StatusBar::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _setSizeHint(_label->getSizeHint());
        }
    }
}