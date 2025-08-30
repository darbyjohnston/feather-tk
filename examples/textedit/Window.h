// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/Label.h>
#include <feather-tk/ui/MainWindow.h>
#include <feather-tk/ui/Menu.h>

namespace ftk
{
    namespace examples
    {
        namespace textedit
        {
            class App;

            class Window : public ftk::MainWindow
            {
            protected:
                void _init(
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<App>&,
                    const std::string& name,
                    const Size2I&);

                Window() = default;

            public:
                virtual ~Window();

                static std::shared_ptr<Window> create(
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<App>&,
                    const std::string& name,
                    const Size2I&);

            private:
                std::map<std::string, std::shared_ptr<Action> > _actions;
                std::map<std::string, std::shared_ptr<Menu> > _menus;
                std::shared_ptr<Label> _textWidget;
                std::shared_ptr<ValueObserver<FontRole> > _fontObserver;
                std::shared_ptr<ValueObserver<std::string> > _textObserver;
            };
        }
    }
}
