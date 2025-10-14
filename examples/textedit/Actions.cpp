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
            _app = app;

            _createFileActions(context, app);
            _createEditActions(context, app);

            _currentDocObserver = ValueObserver<int>::create(
                app->getDocumentModel()->observeCurrentIndex(),
                [this](int index)
                {
                    _selectionObserver.reset();
                    auto app = _app.lock();
                    const auto& documents = app->getDocumentModel()->getList();
                    if (index >= 0 && index < documents.size())
                    {
                        const auto& document = documents[index];
                        _selectionObserver = ValueObserver<TextEditSelection>::create(
                            document->getModel()->observeSelection(),
                            [this](const TextEditSelection&)
                            {
                                _actionsUpdate();
                            });
                    }
                    _actionsUpdate();
                });
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
                    auto app = appWeak.lock();
                    auto document = Document::create(app->getContext(), "Untitled");
                    app->getDocumentModel()->add(document);
                });
            _actions["File/New"]->setTooltip("Create a new file");

            _actions["File/Open"] = Action::create(
                "Open",
                "FileOpen",
                Key::O,
                static_cast<int>(KeyModifier::Control),
                [this, appWeak]
                {
                    auto app = appWeak.lock();
                    auto fileBrowserSystem = app->getContext()->getSystem<FileBrowserSystem>();
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
                    app->getDocumentModel()->close(
                        app->getDocumentModel()->getCurrentIndex());
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
                    app->getDocumentModel()->closeAll();
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
            const std::shared_ptr<ftk::Context>& context,
            const std::shared_ptr<App>& app)
        {
            auto appWeak = std::weak_ptr<App>(app);
            _actions["Edit/Cut"] = Action::create(
                "Cut",
                "Cut",
                [appWeak]
                {
                    auto app = appWeak.lock();
                    if (auto doc = app->getDocumentModel()->getCurrent())
                    {
                        doc->getModel()->key(Key::X, static_cast<int>(KeyModifier::Control));
                    }
                });
            _actions["Edit/Cut"]->setTooltip("Cut the selected text to the clipboard");

            _actions["Edit/Copy"] = Action::create(
                "Copy",
                "Copy",
                [appWeak]
                {
                    auto app = appWeak.lock();
                    if (auto doc = app->getDocumentModel()->getCurrent())
                    {
                        doc->getModel()->key(Key::C, static_cast<int>(KeyModifier::Control));
                    }
                });
            _actions["Edit/Copy"]->setTooltip("Copy the selected text to the clipboard");

            _actions["Edit/Paste"] = Action::create(
                "Paste",
                "Paste",
                [appWeak]
                {
                    auto app = appWeak.lock();
                    if (auto doc = app->getDocumentModel()->getCurrent())
                    {
                        doc->getModel()->key(Key::V, static_cast<int>(KeyModifier::Control));
                    }
                });
            _actions["Edit/Paste"]->setTooltip("Paste text from the clipboard");

            _actions["Edit/SelectAll"] = Action::create(
                "Select All",
                [appWeak]
                {
                    auto app = appWeak.lock();
                    if (auto doc = app->getDocumentModel()->getCurrent())
                    {
                        doc->getModel()->selectAll();
                    }
                });
            _actions["Edit/SelectAll"]->setTooltip("Select all of the text");

            _actions["Edit/ClearSelection"] = Action::create(
                "Clear Selection",
                [appWeak]
                {
                    auto app = appWeak.lock();
                    if (auto doc = app->getDocumentModel()->getCurrent())
                    {
                        doc->getModel()->clearSelection();
                    }
                });
            _actions["Edit/ClearSelection"]->setTooltip("Clear the selection");

            _actions["Edit/Settings"] = Action::create(
                "Settings",
                "Settings",
                [appWeak](bool value)
                {
                    auto app = appWeak.lock();
                    auto options = app->getSettingsModel()->getWindowOptions();
                    options.settings = value;
                    app->getSettingsModel()->setWindowOptions(options);
                });
            _actions["Edit/Settings"]->setTooltip("Toggle the settings");

            _windowOptionsObserver = ValueObserver<WindowOptions>::create(
                app->getSettingsModel()->observeWindowOptions(),
                [this](const WindowOptions& value)
                {
                    _actions["Edit/Settings"]->setChecked(value.settings);
                });
        }

        void Actions::_actionsUpdate()
        {
            auto app = _app.lock();
            auto doc = app->getDocumentModel()->getCurrent();
            TextEditSelection selection;
            if (doc)
            {
                selection = doc->getModel()->getSelection();
            }

            _actions["File/Close"]->setEnabled(doc.get());
            _actions["File/CloseAll"]->setEnabled(doc.get());

            _actions["Edit/Cut"]->setEnabled(doc.get() && selection.isValid());
            _actions["Edit/Copy"]->setEnabled(doc.get() && selection.isValid());
            _actions["Edit/Paste"]->setEnabled(doc.get());
            _actions["Edit/SelectAll"]->setEnabled(doc.get());
            _actions["Edit/ClearSelection"]->setEnabled(doc.get() && selection.isValid());
        }
    }
}