// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "Actions.h"

#include "App.h"
#include "DocumentModel.h"
#include "MainWindow.h"

#include <ftk/UI/FileBrowser.h>

using namespace ftk;

namespace examples
{
    namespace objview
    {
        void Actions::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<MainWindow>& mainWindow)
        {
            // Create the actions.
            _createFileActions(context, app);
            _createEditActions(context, app);
            _createWindowActions(context, app, mainWindow);
            _actionsUpdate();

            // Observe the current document to update the state of the actions.
            _currentObserver = ValueObserver<std::shared_ptr<Document> >::create(
                app->getDocumentModel()->observeCurrent(),
                [this](const std::shared_ptr<Document>& doc)
                {
                    _current = doc;
                    _actionsUpdate();
                });
        }

        Actions::~Actions()
        {}

        std::shared_ptr<Actions> Actions::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<MainWindow>& mainWindow)
        {
            auto out = std::shared_ptr<Actions>(new Actions);
            out->_init(context, app, mainWindow);
            return out;
        }

        const std::map<std::string, std::shared_ptr<Action> > Actions::getActions() const
        {
            return _actions;
        }

        std::shared_ptr<Action> Actions::getAction(const std::string& name) const
        {
            const auto i = _actions.find(name);
            return i != _actions.end() ? i->second : nullptr;
        }

        void Actions::_createFileActions(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app)
        {
            auto appWeak = std::weak_ptr<App>(app);
            _actions["File/Open"] = Action::create(
                "Open",
                "FileOpen",
                Key::O,
                static_cast<int>(KeyModifier::Control),
                [this, appWeak]
                {
                    auto app = appWeak.lock();
                    auto fileBrowserSystem = app->getContext()->getSystem<FileBrowserSystem>();
                    fileBrowserSystem->getModel()->setExtensions({ ".obj" });
                    fileBrowserSystem->open(
                        app->getMainWindow(),
                        [appWeak](const std::filesystem::path& value)
                        {
                            if (auto app = appWeak.lock())
                            {
                                app->open(value);
                            }
                        });
                });
            _actions["File/Open"]->setTooltip("Open a file");

            _actions["File/Close"] = Action::create(
                "Close",
                "FileClose",
                Key::E,
                static_cast<int>(KeyModifier::Control),
                [appWeak]
                {
                    auto app = appWeak.lock();
                    app->close(app->getDocumentModel()->getCurrentIndex());
                });
            _actions["File/Close"]->setTooltip("Close the current file");

            _actions["File/CloseAll"] = Action::create(
                "Close All",
                "FileCloseAll",
                Key::E,
                static_cast<int>(KeyModifier::Shift) |
                static_cast<int>(KeyModifier::Control),
                [appWeak]
                {
                    auto app = appWeak.lock();
                    app->closeAll();
                });
            _actions["File/CloseAll"]->setTooltip("Close all files");

            _actions["File/Exit"] = Action::create(
                "Exit",
                Key::Q,
                static_cast<int>(KeyModifier::Control),
                [appWeak]
                {
                    auto app = appWeak.lock();
                    app->exit();
                });
        }

        void Actions::_createEditActions(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app)
        {
            auto appWeak = std::weak_ptr<App>(app);
            _actions["Edit/Settings"] = Action::create(
                "Settings",
                "Settings",
                [appWeak](bool value)
                {
                    auto app = appWeak.lock();
                    auto window = app->getSettingsModel()->getWindow();
                    window.settings = value;
                    app->getSettingsModel()->setWindow(window);
                });
            _actions["Edit/Settings"]->setTooltip("Toggle the settings");

            _windowSettingsObserver = ValueObserver<WindowSettings>::create(
                app->getSettingsModel()->observeWindow(),
                [this](const WindowSettings& value)
                {
                    _actions["Edit/Settings"]->setChecked(value.settings);
                });
        }

        void Actions::_createWindowActions(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<MainWindow>& mainWindow)
        {
            std::weak_ptr<MainWindow> mainWindowWeak(mainWindow);
            _actions["Window/FullScreen"] = Action::create(
                "Full Screen",
                "WindowFullScreen",
                Key::U,
                static_cast<int>(KeyModifier::Control),
                [mainWindowWeak](bool value)
                {
                    if (auto mainWindow = mainWindowWeak.lock())
                    {
                        mainWindow->setFullScreen(value);
                    }
                });
            _actions["Window/FullScreen"]->setTooltip("Toggle full screen mode");

            _fullScreenObserver = ValueObserver<bool>::create(
                mainWindow->observeFullScreen(),
                [this](bool value)
                {
                    _actions["Window/FullScreen"]->setChecked(value);
                });
        }

        void Actions::_actionsUpdate()
        {
            const auto doc = _current.lock();
            const bool current = doc.get();

            _actions["File/Close"]->setEnabled(current);
            _actions["File/CloseAll"]->setEnabled(current);
        }
    }
}