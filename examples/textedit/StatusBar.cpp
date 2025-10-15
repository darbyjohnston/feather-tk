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

            _cursorLabel = Label::create(context);
            _cursorLabel->setMarginRole(SizeRole::MarginInside);

            _linesLabel = Label::create(context);
            _linesLabel->setMarginRole(SizeRole::MarginInside);

            _layout = HorizontalLayout::create(context, shared_from_this());
            _layout->setSpacingRole(SizeRole::None);
            _layout->addSpacer(Stretch::Expanding);
            _cursorLabel->setParent(_layout);
            _linesLabel->setParent(_layout);

            std::weak_ptr<App> appWeak(app);
            _currentDocumentObserver = ftk::ValueObserver<int>::create(
                app->getDocumentModel()->observeCurrentIndex(),
                [this, appWeak](int index)
                {
                    _textObserver.reset();
                    if (auto app = appWeak.lock())
                    {
                        const auto& documents = app->getDocumentModel()->getList();
                        if (index >= 0 && index < documents.size())
                        {
                            const auto& document = documents[index];
                            _textObserver = ListObserver<std::string>::create(
                                document->getModel()->observeText(),
                                [this](const std::vector<std::string>& lines)
                                {
                                    _linesLabel->setText(Format("Lines: {0}").
                                        arg(lines.size()));
                                });

                            _cursorObserver = ValueObserver<TextEditPos>::create(
                                document->getModel()->observeCursor(),
                                [this](const TextEditPos& value)
                                {
                                    _cursorLabel->setText(Format("Cursor: {0}, {1}").
                                        arg(value.line + 1).
                                        arg(value.chr + 1));
                                });
                        }
                    }
                    if (!_textObserver)
                    {
                        _cursorLabel->setText(std::string());
                        _linesLabel->setText(std::string());
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