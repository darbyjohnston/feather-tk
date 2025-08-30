// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/GridLayout.h>
#include <feather-tk/ui/Icon.h>
#include <feather-tk/ui/IconSystem.h>
#include <feather-tk/ui/Label.h>
#include <feather-tk/ui/MainWindow.h>
#include <feather-tk/ui/ScrollWidget.h>

#include <feather-tk/core/Format.h>

using namespace ftk;

FTK_MAIN()
{
    try
    {
        // Create the context and application.
        auto context = Context::create();
        auto app = App::create(context, argc, argv, "icons", "Icons example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create a window.
        auto window = MainWindow::create(
            context,
            app,
            "icons",
            Size2I(1280, 960));

        // Create a layout.
        auto layout = GridLayout::create(context);
        layout->setRowBackgroundRole(ColorRole::Base);
        layout->setSpacingRole(SizeRole::None);
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Both);
        scrollWidget->setBorder(false);
        scrollWidget->setWidget(layout);
        scrollWidget->setVStretch(Stretch::Expanding);
        window->setWidget(scrollWidget);

        // Create icons.
        auto iconSystem = context->getSystem<IconSystem>();
        int row = 0;
        for (const auto& name : iconSystem->getNames())
        {
            auto icon = Icon::create(context, name, layout);
            layout->setGridPos(icon, row, 0);
            auto label = Label::create(context, name, layout);
            label->setMarginRole(SizeRole::MarginSmall);
            layout->setGridPos(label, row, 1);
            ++row;
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

