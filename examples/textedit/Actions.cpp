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
    namespace textedit
    {
        void Actions::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app)
        {
            _createFileActions(context, app);
            _createEditActions(context, app);
        }

        Actions::~Actions()
        {}

        std::shared_ptr<Actions> Actions::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app)
        {
            auto out = std::shared_ptr<Actions>(new Actions);
            out->_init(context, app);
            return out;
        }

        const std::map<std::string, std::shared_ptr<ftk::Action> > Actions::getActions() const
        {
            return _actions;
        }

        std::shared_ptr<ftk::Action> Actions::getAction(const std::string& name) const
        {
            const auto i = _actions.find(name);
            return i != _actions.end() ? i->second : nullptr;
        }

        void Actions::_createFileActions(
            const std::shared_ptr<ftk::Context>& context,
            const std::shared_ptr<App>& app)
        {
            auto appWeak = std::weak_ptr<App>(app);
            _actions["File/New"] = Action::create(
                "New",
                "FileNew",
                Key::N,
                static_cast<int>(KeyModifier::Control),
                [appWeak]
                {
                    if (auto app = appWeak.lock())
                    {
                        auto document = Document::create(app->getContext(), "Untitled");
                        app->getDocumentModel()->add(document);
                    }
                });
            _actions["File/New"]->setTooltip("Create a new file");

            _actions["File/Open"] = Action::create(
                "Open",
                "FileOpen",
                Key::O,
                static_cast<int>(KeyModifier::Control),
                [this, appWeak]
                {
                    if (auto app = appWeak.lock())
                    {
                        if (auto fileBrowserSystem = app->getContext()->getSystem<FileBrowserSystem>())
                        {
                            fileBrowserSystem->open(
                                app->getMainWindow(),
                                [appWeak](const std::filesystem::path& value)
                                {
                                    if (auto app = appWeak.lock())
                                    {
                                        app->open(value);
                                    }
                                });
                        }
                    }
                });
            _actions["File/Open"]->setTooltip("Open a file");

            _actions["File/Close"] = Action::create(
                "Close",
                "FileClose",
                Key::E,
                static_cast<int>(KeyModifier::Control),
                [appWeak]
                {
                    if (auto app = appWeak.lock())
                    {
                        app->getDocumentModel()->close(
                            app->getDocumentModel()->getCurrent());
                    }
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
                    if (auto app = appWeak.lock())
                    {
                        app->getDocumentModel()->closeAll();
                    }
                });
            _actions["File/CloseAll"]->setTooltip("Close all files");

            _actions["File/Exit"] = Action::create(
                "Exit",
                Key::Q,
                static_cast<int>(KeyModifier::Control),
                [appWeak]
                {
                    if (auto app = appWeak.lock())
                    {
                        app->exit();
                    }
                });
        }

        void Actions::_createEditActions(
            const std::shared_ptr<ftk::Context>& context,
            const std::shared_ptr<App>& app)
        {
            auto appWeak = std::weak_ptr<App>(app);
            _actions["Edit/Settings"] = Action::create(
                "Settings",
                "Settings",
                [appWeak](bool value)
                {
                    if (auto app = appWeak.lock())
                    {
                        auto options = app->getSettingsModel()->getWindowOptions();
                        options.settings = value;
                        app->getSettingsModel()->setWindowOptions(options);
                    }
                });
            _actions["Edit/Settings"]->setTooltip("Toggle the settings");

            _windowOptionsObserver = ValueObserver<WindowOptions>::create(
                app->getSettingsModel()->observeWindowOptions(),
                [this](const WindowOptions& value)
                {
                    _actions["Edit/Settings"]->setChecked(value.settings);
                });
        }
    }
}