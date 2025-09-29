// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/Action.h>
#include <feather-tk/ui/Menu.h>
#include <feather-tk/ui/MenuBar.h>

namespace examples
{
    namespace textedit
    {
        class App;

        class MenuBar : public ftk::MenuBar
        {
        protected:
            void _init(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<App>&,
                const std::shared_ptr<ftk::IWidget>& parent);

            MenuBar() = default;

        public:
            virtual ~MenuBar();

            static std::shared_ptr<MenuBar> create(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<App>&,
                const std::shared_ptr<ftk::IWidget>& parent = nullptr);

        private:
            void _createFileMenu(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<App>&);
            void _createEditMenu(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<App>&);

            std::map<std::string, std::shared_ptr<ftk::Action> > _actions;
            std::map<std::string, std::shared_ptr<ftk::Menu> > _menus;

            std::shared_ptr<ftk::ValueObserver<ftk::FontRole> > _fontObserver;
        };
    }
}