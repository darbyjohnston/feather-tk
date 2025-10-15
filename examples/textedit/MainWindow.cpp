// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "MainWindow.h"

#include "Actions.h"
#include "App.h"
#include "DocumentModel.h"
#include "DocumentTabs.h"
#include "MenuBar.h"
#include "SettingsWidget.h"
#include "StatusBar.h"
#include "ToolBar.h"

#include <ftk/UI/Divider.h>
#include <ftk/UI/RowLayout.h>

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
            _settingsModel = app->getSettingsModel();

            _actions = Actions::create(context, app);

            _menuBar = MenuBar::create(context, _actions);
            setMenuBar(_menuBar);

            _tabs = DocumentTabs::create(context, app);

            _settingsWidget = SettingsWidget::create(context, app);

            _toolBar = ToolBar::create(context, _actions);

            _statusBar = StatusBar::create(context, app);

            _layout = VerticalLayout::create(context, shared_from_this());
            _layout->setSpacingRole(SizeRole::None);
            _layout->setStretch(Stretch::Expanding);
            _toolBar->setParent(_layout);
            Divider::create(context, Orientation::Vertical, _layout);
            _splitter = Splitter::create(context, Orientation::Horizontal, _layout);
            _splitter->setSplit(.7F);
            _tabs->setParent(_splitter);
            _settingsWidget->setParent(_splitter);
            Divider::create(context, Orientation::Vertical, _layout);
            _statusBar->setParent(_layout);
            setWidget(_layout);

            _windowOptionsObserver = ValueObserver<WindowOptions>::create(
                _settingsModel->observeWindowOptions(),
                [this](const WindowOptions& value)
                {
                    _splitter->setSplit(value.split);
                    _settingsWidget->setVisible(value.settings);
                });
        }

        MainWindow::~MainWindow()
        {
            auto windowOptions = _settingsModel->getWindowOptions();
            windowOptions.split = _splitter->getSplit();
            _settingsModel->setWindowOptions(windowOptions);
        }

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