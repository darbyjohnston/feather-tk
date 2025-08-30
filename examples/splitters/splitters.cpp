// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/Label.h>
#include <feather-tk/ui/MainWindow.h>
#include <feather-tk/ui/Splitter.h>

#include <feather-tk/core/Format.h>

using namespace ftk;

FTK_MAIN()
{
    try
    {
        // Create the context and application.
        auto context = Context::create();
        auto app = App::create(context, argc, argv, "splitters", "splitters example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create a window.
        auto window = MainWindow::create(
            context,
            app,
            "splitters",
            Size2I(1280, 960));

        // Create splitters.
        auto splitter = Splitter::create(context, Orientation::Vertical);
        auto splitter2 = Splitter::create(context, Orientation::Horizontal, splitter);
        auto label = Label::create(context, "Label 1", splitter2);
        label->setAlign(HAlign::Center, VAlign::Center);
        label = Label::create(context, "Label 2", splitter2);
        label->setAlign(HAlign::Center, VAlign::Center);
        label = Label::create(context, "Label 3", splitter);
        label->setAlign(HAlign::Center, VAlign::Center);
        window->setWidget(splitter);

        // Show the window and run the application.
        window->show();
        app->run();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

