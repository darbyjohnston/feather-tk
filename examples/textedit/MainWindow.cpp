// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "MainWindow.h"

#include "App.h"
#include "DocumentModel.h"
#include "MenuBar.h"
#include "StatusBar.h"
#include "TextWidget.h"

#include <ftk/UI/Divider.h>
#include <ftk/UI/MenuBar.h>
#include <ftk/UI/RowLayout.h>
#include <ftk/UI/ScrollWidget.h>

using namespace ftk;

namespace examples
{
    namespace textedit
    {
        void MainWindow::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::string& name,
            const Size2I& size)
        {
            ftk::MainWindow::_init(context, app, name, size);

            _app = app;

            _menuBar = MenuBar::create(context, app);
            setMenuBar(_menuBar);

            _tabWidget = TabWidget::create(context);
            _tabWidget->setTabsClosable(true);
            _tabWidget->setStretch(Stretch::Expanding);

            _statusBar = StatusBar::create(context, app);

            _layout = VerticalLayout::create(context, shared_from_this());
            _layout->setSpacingRole(SizeRole::None);
            _layout->setStretch(Stretch::Expanding);
            _tabWidget->setParent(_layout);
            Divider::create(context, Orientation::Vertical, _layout);
            _statusBar->setParent(_layout);
            setWidget(_layout);

            auto appWeak = std::weak_ptr<App>(app);
            _tabWidget->setCurrentTabCallback(
                [appWeak](int index)
                {
                    if (auto app = appWeak.lock())
                    {
                        app->getDocumentModel()->setCurrent(index);
                    }
                });
            _tabWidget->setTabCloseCallback(
                [appWeak](int index)
                {
                    if (auto app = appWeak.lock())
                    {
                        app->getDocumentModel()->remove(index);
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
                            auto textWidget = TextWidget::create(context, document);
                            textWidget->setFontRole(app->getDocumentModel()->getFontRole());
                            _textWidgets.push_back(textWidget);
                            _tabWidget->addTab(
                                document->getName(),
                                textWidget,
                                document->getPath().u8string());
                        }
                    }
                });

            _removeDocumentObserver = ftk::ValueObserver<int>::create(
                app->getDocumentModel()->observeRemove(),
                [this](int index)
                {
                    if (index >= 0 && index < _textWidgets.size())
                    {
                        _textWidgets.erase(_textWidgets.begin() + index);
                        _tabWidget->removeTab(index);
                    }
                });

            _clearDocumentsObserver = ftk::ValueObserver<bool>::create(
                app->getDocumentModel()->observeClear(),
                [this](bool value)
                {
                    if (value)
                    {
                        _textWidgets.clear();
                        _tabWidget->clearTabs();
                    }
                });

            _currentDocumentObserver = ftk::ValueObserver<int>::create(
                app->getDocumentModel()->observeCurrent(),
                [this, appWeak](int index)
                {
                    _tabWidget->setCurrentTab(index);
                });

            _fontObserver = ValueObserver<FontRole>::create(
                app->getDocumentModel()->observeFontRole(),
                [this](FontRole value)
                {
                    for (const auto& widget : _textWidgets)
                    {
                        widget->setFontRole(value);
                    }
                });
        }

        MainWindow::~MainWindow()
        {}

        std::shared_ptr<MainWindow> MainWindow::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::string& name,
            const Size2I& size)
        {
            auto out = std::shared_ptr<MainWindow>(new MainWindow);
            out->_init(context, app, name, size);
            return out;
        }

        void MainWindow::_drop(const std::vector<std::string>& drops)
        {
            if (auto app = _app.lock())
            {
                std::vector<std::filesystem::path> paths;
                for (const auto& drop : drops)
                {
                    paths.push_back(std::filesystem::u8path(drop));
                }
                app->open(paths);
            }
        }
    }
}