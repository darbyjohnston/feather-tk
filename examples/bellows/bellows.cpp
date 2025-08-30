// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/ui/App.h>
#include <ftk/ui/Bellows.h>
#include <ftk/ui/CheckBox.h>
#include <ftk/ui/MainWindow.h>
#include <ftk/ui/PushButton.h>
#include <ftk/ui/RowLayout.h>
#include <ftk/ui/ScrollWidget.h>
#include <ftk/ui/ToolButton.h>

#include <ftk/core/Format.h>

using namespace ftk;

FTK_MAIN()
{
    try
    {
        // Create the context and application.
        auto context = Context::create();
        auto app = App::create(context, argc, argv, "bellows", "Bellows example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create a window.
        auto window = MainWindow::create(
            context,
            app,
            "bellows",
            Size2I(1280, 960));

        // Create a layout.
        auto layout = VerticalLayout::create(context);
        layout->setSpacingRole(SizeRole::None);
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Both);
        scrollWidget->setBorder(false);
        scrollWidget->setWidget(layout);
        scrollWidget->setVStretch(Stretch::Expanding);
        window->setWidget(scrollWidget);

        // Add a bellows.
        auto vLayout = VerticalLayout::create(context);
        vLayout->setMarginRole(SizeRole::Margin);
        vLayout->setSpacingRole(SizeRole::SpacingSmall);
        for (size_t i = 0; i < 10; ++i)
        {
            PushButton::create(context, Format("Push Button {0}").arg(i), vLayout);
        }
        auto bellows = Bellows::create(context, "Push Buttons", layout);
        bellows->setWidget(vLayout);

        // Add a bellows.
        vLayout = VerticalLayout::create(context);
        vLayout->setMarginRole(SizeRole::Margin);
        vLayout->setSpacingRole(SizeRole::SpacingSmall);
        const std::vector<std::string> icons =
        {
            "Audio",
            "Close",
            "Copy",
            "Directory",
            "File",
            "FrameNext",
            "FramePrev",
            "Mute",
            "Search",
            "Volume"
        };
        for (size_t i = 0; i < 10; ++i)
        {
            auto button = ToolButton::create(context, Format("Tool Button {0}").arg(i), vLayout);
            if (i < icons.size())
            {
                button->setIcon(icons[i]);
            }
        }
        bellows = Bellows::create(context, "Tool Buttons", layout);
        bellows->setWidget(vLayout);

        // Add a bellows.
        vLayout = VerticalLayout::create(context);
        vLayout->setMarginRole(SizeRole::Margin);
        vLayout->setSpacingRole(SizeRole::SpacingSmall);
        for (size_t i = 0; i < 10; ++i)
        {
            CheckBox::create(context, Format("Check Box {0}").arg(i), vLayout);
        }
        bellows = Bellows::create(context, "Check Boxes", layout);
        bellows->setWidget(vLayout);

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

