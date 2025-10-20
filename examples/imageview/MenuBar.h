// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/Action.h>
#include <ftk/UI/Menu.h>
#include <ftk/UI/MenuBar.h>

namespace imageview
{
    class Actions;
    class App;

    //! Menu bar.
    class MenuBar : public ftk::MenuBar
    {
    protected:
        void _init(
            const std::shared_ptr<ftk::Context>&,
            const std::shared_ptr<App>&,
            const std::shared_ptr<Actions>&,
            const std::shared_ptr<ftk::IWidget>& parent);

        MenuBar() = default;

    public:
        virtual ~MenuBar();

        //! Create a new menu bar.
        static std::shared_ptr<MenuBar> create(
            const std::shared_ptr<ftk::Context>&,
            const std::shared_ptr<App>&,
            const std::shared_ptr<Actions>&,
            const std::shared_ptr<ftk::IWidget>& parent = nullptr);

    private:
        void _createFileMenu(
            const std::shared_ptr<ftk::Context>&,
            const std::shared_ptr<Actions>&);
        void _createEditMenu(
            const std::shared_ptr<ftk::Context>&,
            const std::shared_ptr<Actions>&);
        void _createWindowMenu(
            const std::shared_ptr<ftk::Context>&,
            const std::shared_ptr<Actions>&);

        std::map<std::string, std::shared_ptr<ftk::Menu> > _menus;

        std::shared_ptr<ftk::ListObserver<std::filesystem::path> > _recentFilesObserver;
    };
}
