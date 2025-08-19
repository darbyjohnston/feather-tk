// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/FileEditTest.h>

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/FileBrowser.h>
#include <feather-tk/ui/FileEdit.h>
#include <feather-tk/ui/RowLayout.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        FileEditTest::FileEditTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::FileEditTest")
        {}

        FileEditTest::~FileEditTest()
        {}

        std::shared_ptr<FileEditTest> FileEditTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FileEditTest>(new FileEditTest(context));
        }

        void FileEditTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("FileEditTest");
                auto app = App::create(
                    context,
                    argv,
                    "FileEditTest",
                    "File edit test.");
                auto window = Window::create(context, "FileEditTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto edit = FileEdit::create(context, layout);
                std::filesystem::path path = std::filesystem::current_path();
                edit->setPath(path);
                edit->setPath(path);
                FEATHER_TK_ASSERT(path == edit->getPath());
                edit->setCallback(
                    [&path](const std::filesystem::path& value)
                    {
                        path = value;
                    });

                auto system = context->getSystem<FileBrowserSystem>();
                system->setNativeFileDialog(false);
                FEATHER_TK_ASSERT(!system->isNativeFileDialog());
            }
        }
    }
}

