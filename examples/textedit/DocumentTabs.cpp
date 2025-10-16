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
                    auto app = appWeak.lock();
                    app->getDocumentModel()->setCurrentIndex(index);
                });
            _tabWidget->setTabCloseCallback(
                [appWeak](int index)
                {
                    auto app = appWeak.lock();
                    app->getDocumentModel()->close(index);
                });

            _addDocumentObserver = ftk::ValueObserver<std::shared_ptr<Document> >::create(
                app->getDocumentModel()->observeAdd(),
                [this, appWeak](const std::shared_ptr<Document>& doc)
                {
                    if (doc)
                    {
                        auto context = getContext();
                        auto app = appWeak.lock();
                        auto textEdit = TextEdit::create(context, doc->getModel());
                        textEdit->setOptions(app->getSettingsModel()->getTextEditOptions());
                        textEdit->getModel()->setOptions(app->getSettingsModel()->getTextEditModelOptions());
                        textEdit->setMarginRole(SizeRole::MarginSmall);
                        _textEdits[doc] = textEdit;
                        _tabWidget->addTab(std::string(), textEdit);
                        textEdit->takeKeyFocus();

                        _documentPathObservers[doc] = ValueObserver<std::filesystem::path>::create(
                            doc->observePath(),
                            [this, textEdit](const std::filesystem::path& path)
                            {
                                const std::string text = path.filename().u8string();
                                const std::string tooltip = path.u8string();
                                _tabWidget->setText(
                                    textEdit,
                                    !text.empty() ? text : "Untitled",
                                    !tooltip.empty() ? tooltip : "Untitled");
                            });
                    }
                });

            _removeDocumentObserver = ftk::ValueObserver<std::shared_ptr<Document> >::create(
                app->getDocumentModel()->observeClose(),
                [this, appWeak](const std::shared_ptr<Document>& doc)
                {
                    auto app = appWeak.lock();
                    auto i = _textEdits.find(doc);
                    if (i != _textEdits.end())
                    {
                        _tabWidget->removeTab(i->second);
                        _textEdits.erase(i);
                    }
                    auto j = _documentPathObservers.find(doc);
                    if (j != _documentPathObservers.end())
                    {
                        _documentPathObservers.erase(j);
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
                        _documentPathObservers.clear();
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
                    for (auto i : _textEdits)
                    {
                        i.second->setOptions(value);
                    }
                });

            _textEditModelOptionsObserver = ValueObserver<TextEditModelOptions>::create(
                app->getSettingsModel()->observeTextEditModelOptions(),
                [this](const TextEditModelOptions& value)
                {
                    for (auto i : _textEdits)
                    {
                        i.second->getModel()->setOptions(value);
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