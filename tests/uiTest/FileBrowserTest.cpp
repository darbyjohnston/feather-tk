// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/FileBrowserTest.h>

#include <ftk/ui/App.h>
#include <ftk/ui/FileBrowserPrivate.h>
#include <ftk/ui/RecentFilesModel.h>
#include <ftk/ui/RowLayout.h>
#include <ftk/ui/Window.h>

#include <ftk/core/Assert.h>
#include <ftk/core/Format.h>
#include <ftk/core/Time.h>

namespace ftk
{
    namespace ui_test
    {
        FileBrowserTest::FileBrowserTest(const std::shared_ptr<Context>& context) :
            ITest(context, "ftk::ui_test::FileBrowserTest")
        {}

        FileBrowserTest::~FileBrowserTest()
        {}

        std::shared_ptr<FileBrowserTest> FileBrowserTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FileBrowserTest>(new FileBrowserTest(context));
        }
                
        void FileBrowserTest::run()
        {
            _enums();
            _shortcuts();
            _view();
            _widget();
            _dialog();
        }

        void FileBrowserTest::_enums()
        {
            FTK_TEST_ENUM(FileBrowserSort);
        }

        void FileBrowserTest::_shortcuts()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("FileBrowserTest");
                auto app = App::create(
                    context,
                    argv,
                    "FileBrowserTest",
                    "File browser test.");
                auto window = Window::create(context, "FileBrowserTest");
                app->addWindow(window);
                window->show();
                app->tick();

                auto model = FileBrowserModel::create(context);
                auto panel = FileBrowserPanel::create(context, model, window);
                auto recentFilesModel = RecentFilesModel::create(context);
                recentFilesModel->addRecent(std::filesystem::current_path());
                panel->setRecentFilesModel(recentFilesModel);
            }
        }

        void FileBrowserTest::_view()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("FileBrowserTest");
                auto app = App::create(
                    context,
                    argv,
                    "FileBrowserTest",
                    "File browser test.");
                auto window = Window::create(context, "FileBrowserTest");
                app->addWindow(window);
                window->show();
                app->tick();

                auto model = FileBrowserModel::create(context);
                auto view = FileBrowserView::create(context, FileBrowserMode::File, model, window);
                std::filesystem::path path = std::filesystem::current_path();
                model->setPath(path);
                model->setPath(path);
                FTK_ASSERT(path == model->getPath());
                view->reload();
                FileBrowserOptions options;
                options.reverseSort = true;
                model->setOptions(options);
                model->setOptions(options);
                FTK_ASSERT(options == model->getOptions());
                view->setCallback(
                    [&path](const std::filesystem::path& value)
                    {
                        path = value;
                    });

                options.sort = FileBrowserSort::Extension;
                model->setOptions(options);
                app->tick();
                options.sort = FileBrowserSort::Size;
                model->setOptions(options);
                app->tick();
                options.sort = FileBrowserSort::Time;
                model->setOptions(options);
                app->tick();
            }
        }

        void FileBrowserTest::_widget()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("FileBrowserTest");
                auto app = App::create(
                    context,
                    argv,
                    "FileBrowserTest",
                    "File browser test.");
                auto window = Window::create(context, "FileBrowserTest");
                app->addWindow(window);
                window->show();
                app->tick();

                std::filesystem::path path = std::filesystem::current_path();
                auto model = FileBrowserModel::create(context);
                auto fileBrowserWidget = FileBrowserWidget::create(
                    context,
                    path,
                    FileBrowserMode::File,
                    model,
                    window);
                FileBrowserOptions options;
                options.reverseSort = true;
                model->setOptions(options);
                model->setOptions(options);
                FTK_ASSERT(options == model->getOptions());
                auto recentFilesModel = RecentFilesModel::create(context);
                fileBrowserWidget->setRecentFilesModel(recentFilesModel);
                fileBrowserWidget->setCallback(
                    [&path](const std::filesystem::path& value)
                    {
                        path = value;
                    });
                bool cancel = false;
                fileBrowserWidget->setCancelCallback(
                    [&cancel]
                    {
                        cancel = true;
                    });
            }
        }

        void FileBrowserTest::_dialog()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("FileBrowserTest");
                auto app = App::create(
                    context,
                    argv,
                    "FileBrowserTest",
                    "File browser test.");
                auto window = Window::create(context, "FileBrowserTest");
                app->addWindow(window);
                window->show();
                app->tick();

                std::filesystem::path path = std::filesystem::current_path();
                auto model = FileBrowserModel::create(context);
                auto fileBrowser = FileBrowser::create(context, path, FileBrowserMode::File, model);
                FileBrowserOptions options;
                options.reverseSort = true;
                model->setOptions(options);
                FTK_ASSERT(model->getOptions() == options);
                auto recentFilesModel = RecentFilesModel::create(context);
                fileBrowser->setRecentFilesModel(recentFilesModel);
                FTK_ASSERT(recentFilesModel == fileBrowser->getRecentFilesModel());
                fileBrowser->setCallback(
                    [&path](const std::filesystem::path& value)
                    {
                        path = value;
                    });
                bool close = false;
                fileBrowser->setCloseCallback(
                    [&close]
                    {
                        close = true;
                    });

                fileBrowser->open(window);
                app->tick();
                FTK_ASSERT(fileBrowser->isOpen());
                fileBrowser->close();
                app->tick();
                FTK_ASSERT(!fileBrowser->isOpen());
            }
        }
    }
}

