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
            const std::shared_ptr<Actions>& actions,
            const std::shared_ptr<IWidget>& parent)
        {
            ftk::MenuBar::_init(context, parent);

            _menus["File"] = Menu::create(context);
            _menus["File"]->addAction(actions->getAction("File/New"));
            _menus["File"]->addAction(actions->getAction("File/Open"));
            _menus["File"]->addAction(actions->getAction("File/Close"));
            _menus["File"]->addAction(actions->getAction("File/CloseAll"));
            _menus["File"]->addDivider();
            _menus["File"]->addAction(actions->getAction("File/Exit"));
            addMenu("File", _menus["File"]);

            _menus["Edit"] = Menu::create(context);
            _menus["Edit"]->addAction(actions->getAction("Edit/Settings"));
            addMenu("Edit", _menus["Edit"]);
        }

        MenuBar::~MenuBar()
        {}

        std::shared_ptr<MenuBar> MenuBar::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<Actions>& actions,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<MenuBar>(new MenuBar);
            out->_init(context, actions, parent);
            return out;
        }
    }
}