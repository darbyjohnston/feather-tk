// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include "Settings.h"

#include <ftk/UI/MainWindow.h>
#include <ftk/UI/RowLayout.h>
#include <ftk/UI/Splitter.h>

namespace imageview
{
    class Actions;
    class App;
    class DocumentTabs;
    class MenuBar;
    class ImageView;
    class SettingsModel;
    class SettingsWidget;
    class StatusBar;
    class ToolBar;

    //! Main window.
    class MainWindow : public ftk::MainWindow
    {
    protected:
        void _init(
            const std::shared_ptr<ftk::Context>&,
            const std::shared_ptr<App>&,
            const std::string& name,
            const ftk::Size2I&);

        MainWindow() = default;

    public:
        virtual ~MainWindow();

        //! Create a new window.
        static std::shared_ptr<MainWindow> create(
            const std::shared_ptr<ftk::Context>&,
            const std::shared_ptr<App>&,
            const std::string& name,
            const ftk::Size2I&);

        //! \name Current View
        ///@{

        const std::shared_ptr<ImageView>& getCurrentView() const;
        std::shared_ptr<ftk::IObservableValue<std::shared_ptr<ImageView> > > observeCurrentView() const;

        ///@}

    protected:
        void _drop(const std::vector<std::string>&) override;
 
    private:

        std::weak_ptr<App> _app;
        std::shared_ptr<SettingsModel> _settingsModel;
        std::shared_ptr<ftk::ObservableValue<std::shared_ptr<ImageView> > > _currentView;

        std::shared_ptr<Actions> _actions;
        std::shared_ptr<MenuBar> _menuBar;
        std::shared_ptr<ToolBar> _toolBar;
        std::shared_ptr<DocumentTabs> _tabs;
        std::shared_ptr<SettingsWidget> _settingsWidget;
        std::shared_ptr<StatusBar> _statusBar;
        std::shared_ptr<ftk::Splitter> _splitter;
        std::shared_ptr<ftk::VerticalLayout> _layout;

        std::shared_ptr<ftk::ValueObserver<std::shared_ptr<ImageView> > > _currentViewObserver;
        std::shared_ptr<ftk::ValueObserver<WindowSettings> > _windowSettingsObserver;
    };
}
