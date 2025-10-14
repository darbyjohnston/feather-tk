// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "DocumentTabs.h"

#include "App.h"
#include "DocumentModel.h"
#include "SettingsModel.h"

using namespace ftk;

namespace examples
{
    namespace textedit
    {
        void DocumentTabs::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "examples::textedit::DocumentTabs", parent);

            setStretch(Stretch::Expanding);

            _tabWidget = TabWidget::create(context, shared_from_this());
            _tabWidget->setTabsClosable(true);

            auto appWeak = std::weak_ptr<App>(app);
            _tabWidget->setCurrentTabCallback(
                [appWeak](int index)
                {
                    if (auto app = appWeak.lock())
                    {
                        app->getDocumentModel()->setCurrentIndex(index);
                    }
                });
            _tabWidget->setTabCloseCallback(
                [appWeak](int index)
                {
                    if (auto app = appWeak.lock())
                    {
                        app->getDocumentModel()->close(index);
                    }
                });

            _addDocumentObserver = ftk::ValueObserver<std::shared_ptr<Document> >::create(
                app->getDocumentModel()->observeAdd(),
                [this, appWeak](const std::shared_ptr<Document>& document)
                {
                    if (document)
                    {
                        auto context = getContext();
                        auto app = appWeak.lock();
                        if (context && app)
                        {
                            auto textEdit = TextEdit::create(context, document->getModel());
                            textEdit->setOptions(app->getSettingsModel()->getTextEditOptions());
                            textEdit->setMarginRole(SizeRole::MarginSmall);
                            _textEdits.push_back(textEdit);
                            _tabWidget->addTab(
                                document->getName(),
                                textEdit,
                                document->getPath().u8string());
                        }
                    }
                });

            _removeDocumentObserver = ftk::ValueObserver<int>::create(
                app->getDocumentModel()->observeClose(),
                [this](int index)
                {
                    if (index >= 0 && index < _textEdits.size())
                    {
                        _textEdits.erase(_textEdits.begin() + index);
                        _tabWidget->removeTab(index);
                    }
                });

            _clearDocumentsObserver = ftk::ValueObserver<bool>::create(
                app->getDocumentModel()->observeCloseAll(),
                [this](bool value)
                {
                    if (value)
                    {
                        _textEdits.clear();
                        _tabWidget->clearTabs();
                    }
                });

            _currentDocumentObserver = ftk::ValueObserver<int>::create(
                app->getDocumentModel()->observeCurrentIndex(),
                [this, appWeak](int index)
                {
                    _tabWidget->setCurrentTab(index);
                });

            _textEditOptionsObserver = ValueObserver<TextEditOptions>::create(
                app->getSettingsModel()->observeTextEditOptions(),
                [this](const TextEditOptions& value)
                {
                    for (const auto& widget : _textEdits)
                    {
                        widget->setOptions(value);
                    }
                });
        }

        DocumentTabs::~DocumentTabs()
        {}

        std::shared_ptr<DocumentTabs> DocumentTabs::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<DocumentTabs>(new DocumentTabs);
            out->_init(context, app, parent);
            return out;
        }

        void DocumentTabs::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            _tabWidget->setGeometry(value);
        }

        void DocumentTabs::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _setSizeHint(_tabWidget->getSizeHint());
        }
    }
}