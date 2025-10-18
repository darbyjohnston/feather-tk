// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "DocumentTabs.h"

#include "App.h"
#include "DocumentModel.h"
#include "SettingsModel.h"

#include <ftk/UI/Label.h>

using namespace ftk;

namespace examples
{
    namespace imageview
    {
        void DocumentTabs::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "examples::imageview::DocumentTabs", parent);

            setStretch(Stretch::Expanding);

            _tabWidget = TabWidget::create(context, shared_from_this());
            _tabWidget->setTabsClosable(true);

            // Set tab callbacks.
            auto appWeak = std::weak_ptr<App>(app);
            _tabWidget->setCurrentTabCallback(
                [appWeak](int index)
                {
                    auto app = appWeak.lock();
                    app->getDocumentModel()->setCurrentIndex(index);
                });
            _tabWidget->setTabCloseCallback(
                [appWeak](int index)
                {
                    auto app = appWeak.lock();
                    app->close(index);
                });

            // Observe when documents are added.
            _addObserver = ftk::ValueObserver<std::weak_ptr<Document> >::create(
                app->getDocumentModel()->observeAdd(),
                [this, appWeak](const std::weak_ptr<Document>& docWeak)
                {
                    if (auto doc = docWeak.lock())
                    {
                        // Create a new view.
                        auto context = getContext();
                        auto app = appWeak.lock();
                        auto view = Label::create(context, "View");
                        _views[doc] = view;
                        _tabWidget->addTab(doc->getName(), view, doc->getTooltip());
                        view->takeKeyFocus();
                    }
                });

            // Observe when documents are closed.
            _closeObserver = ftk::ValueObserver<std::weak_ptr<Document> >::create(
                app->getDocumentModel()->observeClose(),
                [this](const std::weak_ptr<Document>& docWeak)
                {
                    if (auto doc = docWeak.lock())
                    {
                        // Remove the view.
                        auto i = _views.find(doc);
                        if (i != _views.end())
                        {
                            _tabWidget->removeTab(i->second);
                            _views.erase(i);
                        }
                    }
                });

            // Observe when all the documents are closed.
            _clearObserver = ftk::ValueObserver<bool>::create(
                app->getDocumentModel()->observeCloseAll(),
                [this](bool value)
                {
                    if (value)
                    {
                        _views.clear();
                        _tabWidget->clearTabs();
                    }
                });

            // Observe the current document and update the current tab.
            _currentObserver = ftk::ValueObserver<int>::create(
                app->getDocumentModel()->observeCurrentIndex(),
                [this, appWeak](int index)
                {
                    _tabWidget->setCurrentTab(index);
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