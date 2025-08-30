// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "App.h"

#include "Window.h"

#include <ftk/ui/DialogSystem.h>
#include <ftk/ui/FileBrowser.h>

#include <ftk/core/FileIO.h>

using namespace ftk;

namespace ftk
{
    namespace examples
    {
        namespace textedit
        {
            void App::_init(
                const std::shared_ptr<Context>& context,
                const std::vector<std::string>& argv)
            {
                _cmdLine.path = CmdLineValueArg<std::string>::create(
                    "input",
                    "Input path.",
                    true);

                ftk::App::_init(
                    context,
                    argv,
                    "textedit",
                    "Text edit example",
                    { _cmdLine.path });

                _font = ObservableValue<FontRole>::create(FontRole::Mono);
                _text = ObservableValue<std::string>::create();

                context->getSystem<FileBrowserSystem>()->setNativeFileDialog(false);

                _window = Window::create(
                    context,
                    std::dynamic_pointer_cast<App>(shared_from_this()),
                    "textedit",
                    Size2I(1280, 960));

                if (_cmdLine.path->hasValue())
                {
                    open(_cmdLine.path->getValue());
                }

                _window->show();
            }

            std::shared_ptr<App> App::create(
                const std::shared_ptr<Context>& context,
                const std::vector<std::string>& argv)
            {
                auto out = std::shared_ptr<App>(new App);
                out->_init(context, argv);
                return out;
            }

            std::shared_ptr<IObservableValue<FontRole> > App::observeFont() const
            {
                return _font;
            }

            void App::setFont(FontRole value)
            {
                _font->setIfChanged(value);
            }

            std::shared_ptr<IObservableValue<std::string> > App::observeText() const
            {
                return _text;
            }

            void App::open(const std::filesystem::path& path)
            {
                try
                {
                    auto fileIO = FileIO::create(path, FileMode::Read);
                    const std::string text = read(fileIO);
                    _text->setIfChanged(text);
                }
                catch (const std::exception& e)
                {
                    _context->getSystem<DialogSystem>()->message("ERROR", e.what(), _window);
                }
            }
        }
    }
}
