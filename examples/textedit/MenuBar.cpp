// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "MenuBar.h"

#include "App.h"
#include "DocumentModel.h"

#include <feather-tk/ui/FileBrowser.h>

#include <feather-tk/core/String.h>

using namespace ftk;

namespace examples
{
    namespace textedit
    {
        void MenuBar::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<IWidget>& parent)
        {
            ftk::MenuBar::_init(context, parent);

            _createFileMenu(context, app);
            _createEditMenu(context, app);
            addMenu("File", _menus["File"]);
            addMenu("Edit", _menus["Edit"]);
        }

        MenuBar::~MenuBar()
        {}

        std::shared_ptr<MenuBar> MenuBar::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<MenuBar>(new MenuBar);
            out->_init(context, app, parent);
            return out;
        }

        void MenuBar::_createFileMenu(
            const std::shared_ptr<ftk::Context>& context,
            const std::shared_ptr<App>& app)
        {
            _menus["File"] = Menu::create(context);

            auto appWeak = std::weak_ptr<App>(app);
            _actions["File/Open"] = Action::create(
                "Open",
                "FileOpen",
                Key::O,
                static_cast<int>(KeyModifier::Control),
                [this, appWeak]
                {
                    if (auto context = getContext())
                    {
                        if (auto fileBrowserSystem = context->getSystem<FileBrowserSystem>())
                        {
                            fileBrowserSystem->open(
                                getWindow(),
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
            _menus["File"]->addAction(_actions["File/Open"]);

            _actions["File/Close"] = Action::create(
                "Close",
                "FileClose",
                Key::E,
                static_cast<int>(KeyModifier::Control),
                [this]
                {
                });
            _menus["File"]->addAction(_actions["File/Close"]);

            _menus["File"]->addDivider();

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
            _menus["File"]->addAction(_actions["File/Exit"]);
        }

        void MenuBar::_createEditMenu(
            const std::shared_ptr<ftk::Context>& context,
            const std::shared_ptr<App>& app)
        {
            _menus["Edit"] = Menu::create(context);

            auto appWeak = std::weak_ptr<App>(app);
            _menus["Edit/Font"] = _menus["Edit"]->addSubMenu("Font");
            _actions["Edit/Font/Monospace"] = Action::create(
                "Monospace",
                [appWeak]
                {
                    if (auto app = appWeak.lock())
                    {
                        app->getDocumentModel()->setFontRole(FontRole::Mono);
                    }
                });
            _menus["Edit/Font"]->addAction(_actions["Edit/Font/Monospace"]);
            _actions["Edit/Font/Regular"] = Action::create(
                "Regular",
                [appWeak]
                {
                    if (auto app = appWeak.lock())
                    {
                        app->getDocumentModel()->setFontRole(FontRole::Label);
                    }
                });
            _menus["Edit/Font"]->addAction(_actions["Edit/Font/Regular"]);

            _fontObserver = ValueObserver<FontRole>::create(
                app->getDocumentModel()->observeFontRole(),
                [this](FontRole value)
                {
                    _menus["Edit/Font"]->setChecked(
                        _actions["Edit/Font/Monospace"],
                        FontRole::Mono == value);
                    _menus["Edit/Font"]->setChecked(
                        _actions["Edit/Font/Regular"],
                        FontRole::Label == value);
                });
        }
    }
}