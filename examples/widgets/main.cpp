// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "MainWindow.h"

#include <ftk/UI/App.h>
#include <ftk/UI/FileBrowser.h>

FTK_MAIN()
{
    try
    {
        // Create the context and application.
        auto context = ftk::Context::create();
        auto app = ftk::App::create(context, argc, argv, "bellows", "Bellows example");
        if (app->getExit() != 0)
            return app->getExit();

        // Initialize the file browser.
        auto fileBrowserSystem = context->getSystem<FileBrowserSystem>();
        fileBrowserSystem->setNativeFileDialog(false);

        // Create the window.
        auto window = widgets::MainWindow::create(context, app);

        // Run the application.
        app->run();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

