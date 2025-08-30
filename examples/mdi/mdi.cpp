// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/ui/App.h>
#include <ftk/ui/ColorWidget.h>
#include <ftk/ui/MDICanvas.h>
#include <ftk/ui/MDIWidget.h>
#include <ftk/ui/MainWindow.h>
#include <ftk/ui/ScrollWidget.h>

#include <ftk/core/Format.h>
#include <ftk/core/Random.h>

using namespace ftk;

FTK_MAIN()
{
    try
    {
        // Create the context and application.
        auto context = Context::create();
        auto app = App::create(context, argc, argv, "mdi", "MDI example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create a window.
        const Size2I size(1280, 720);
        auto window = MainWindow::create(context, app, "mdi", size);

        // Create a scroll widget.
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Both);
        scrollWidget->setBorder(false);
        scrollWidget->setVStretch(Stretch::Expanding);
        window->setWidget(scrollWidget);

        // Create a MDI canvas.
        auto canvas = MDICanvas::create(context);
        scrollWidget->setWidget(canvas);

        // Create MDI widgets.
        Random random;
        for (size_t i = 0; i < 10; ++i)
        {
            auto colorWidget = ColorWidget::create(context);
            colorWidget->setColor(Color4F(random.getF(), random.getF(), random.getF()));
            canvas->addWidget(
                Format("Color {0}").arg(i),
                V2I(random.getI(0, size.w), random.getI(0, size.h)),
                colorWidget);
        }

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

