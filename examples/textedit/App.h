// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/Style.h>

#include <feather-tk/core/CmdLine.h>
#include <feather-tk/core/ObservableValue.h>

#include <filesystem>

namespace ftk
{
    namespace examples
    {
        namespace textedit
        {
            class Window;

            class App : public ftk::App
            {
            protected:
                void _init(
                    const std::shared_ptr<Context>&,
                    const std::vector<std::string>& argv);

                App() = default;

            public:
                virtual ~App() = default;

                static std::shared_ptr<App> create(
                    const std::shared_ptr<Context>&,
                    const std::vector<std::string>&);

                std::shared_ptr<IObservableValue<FontRole> > observeFont() const;

                void setFont(FontRole);

                std::shared_ptr<IObservableValue<std::string> > observeText() const;

                void open(const std::filesystem::path&);

            private:
                struct CmdLine
                {
                    std::shared_ptr<CmdLineValueArg<std::string> > path;
                };
                CmdLine _cmdLine;
                std::shared_ptr<ObservableValue<FontRole> > _font;
                std::shared_ptr<ObservableValue<std::string> > _text;
                std::shared_ptr<Window> _window;
            };
        }
    }
}
