// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "MenuBar.h"

#include "Actions.h"
#include "App.h"

#include <ftk/UI/RecentFilesModel.h>

using namespace ftk;

namespace imageview
{
    void MenuBar::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<App>& app,
        const std::shared_ptr<Actions>& actions,
        const std::shared_ptr<IWidget>& parent)
    {
        ftk::MenuBar::_init(context, parent);

        // Create the menus.
        _createFileMenu(context, actions);
        _createEditMenu(context, actions);
        _createWindowMenu(context, actions);

        // Observe the recent files and update the menu.
        std::weak_ptr<App> appWeak(app);
        _recentFilesObserver = ListObserver<std::filesystem::path>::create(
            app->getRecentFilesModel()->observeRecent(),
            [this, appWeak](const std::vector<std::filesystem::path>& value)
            {
                _menus["File/Recent"]->clear();
                for (auto i = value.rbegin(); i != value.rend(); ++i)
                {
                    const std::filesystem::path path = *i;
                    auto action = Action::create(
                        path.filename().u8string(),
                        [appWeak, path]
                        {
                            auto app = appWeak.lock();
                            app->open(path);
                        });
                    _menus["File/Recent"]->addAction(action);
                }
            });
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
        const std::shared_ptr<Actions>& actions)
    {
        _menus["File"] = Menu::create(context);
        _menus["File"]->addAction(actions->getAction("File/Open"));
        _menus["File"]->addAction(actions->getAction("File/Close"));
        _menus["File"]->addAction(actions->getAction("File/CloseAll"));
        _menus["File"]->addDivider();
        _menus["File/Recent"] = _menus["File"]->addSubMenu("Recent");
        _menus["File"]->addDivider();
        _menus["File"]->addAction(actions->getAction("File/Exit"));
        addMenu("File", _menus["File"]);
    }

    void MenuBar::_createEditMenu(
        const std::shared_ptr<ftk::Context>& context,
        const std::shared_ptr<Actions>& actions)
    {
        _menus["Edit"] = Menu::create(context);
        _menus["Edit"]->addAction(actions->getAction("Edit/Settings"));
        addMenu("Edit", _menus["Edit"]);
    }

    void MenuBar::_createWindowMenu(
        const std::shared_ptr<ftk::Context>& context,
        const std::shared_ptr<Actions>& actions)
    {
        _menus["Window"] = Menu::create(context);
        _menus["Window"]->addAction(actions->getAction("Window/FullScreen"));
        addMenu("Window", _menus["Window"]);
    }
}
