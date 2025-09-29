// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <UiTest/FileEditTest.h>

#include <ftk/Ui/App.h>
#include <ftk/Ui/FileBrowser.h>
#include <ftk/Ui/FileEdit.h>
#include <ftk/Ui/RowLayout.h>
#include <ftk/Ui/Window.h>

#include <ftk/Core/Assert.h>
#include <ftk/Core/Format.h>

namespace ftk
{
    namespace ui_test
    {
        FileEditTest::FileEditTest(const std::shared_ptr<Context>& context) :
            ITest(context, "ftk::ui_test::FileEditTest")
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
                FTK_ASSERT(path == edit->getPath());
                edit->setCallback(
                    [&path](const std::filesystem::path& value)
                    {
                        path = value;
                    });

                auto system = context->getSystem<FileBrowserSystem>();
                system->setNativeFileDialog(false);
                FTK_ASSERT(!system->isNativeFileDialog());
            }
        }
    }
}

