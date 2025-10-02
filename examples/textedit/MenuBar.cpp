// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "MenuBar.h"

#include "Actions.h"

using namespace ftk;

namespace examples
{
    namespace textedit
    {
        void MenuBar::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<Actions>& actions,
            const std::shared_ptr<IWidget>& parent)
        {
            ftk::MenuBar::_init(context, parent);

            _actions = actions;

            _createFileMenu(context, app);
            _createEditMenu(context, app);
        }

        MenuBar::~MenuBar()
        {}

        std::shared_ptr<MenuBar> MenuBar::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<Actions>& actions,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<MenuBar>(new MenuBar);
            out->_init(context, app, actions, parent);
            return out;
        }

        void MenuBar::_createFileMenu(
            const std::shared_ptr<ftk::Context>& context,
            const std::shared_ptr<App>& app)
        {
            _menus["File"] = Menu::create(context);

            _menus["File"]->addAction(_actions->getAction("File/New"));
            _menus["File"]->addAction(_actions->getAction("File/Open"));
            _menus["File"]->addAction(_actions->getAction("File/Close"));
            _menus["File"]->addAction(_actions->getAction("File/CloseAll"));

            _menus["File"]->addDivider();

            _menus["File"]->addAction(_actions->getAction("File/Exit"));

            addMenu("File", _menus["File"]);
        }

        void MenuBar::_createEditMenu(
            const std::shared_ptr<ftk::Context>& context,
            const std::shared_ptr<App>& app)
        {
            _menus["Edit"] = Menu::create(context);

            _menus["Edit"]->addAction(_actions->getAction("Edit/Settings"));

            addMenu("Edit", _menus["Edit"]);
        }
    }
}