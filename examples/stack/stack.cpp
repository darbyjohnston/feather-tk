// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/ui/App.h>
#include <ftk/ui/Divider.h>
#include <ftk/ui/Label.h>
#include <ftk/ui/MainWindow.h>
#include <ftk/ui/PushButton.h>
#include <ftk/ui/RowLayout.h>
#include <ftk/ui/StackLayout.h>

#include <ftk/core/Format.h>

using namespace ftk;

FTK_MAIN()
{
    try
    {
        // Create the context and application.
        auto context = Context::create();
        auto app = App::create(context, argc, argv, "stack", "Stack example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create a window.
        auto window = MainWindow::create(
            context,
            app,
            "stack",
            Size2I(1280, 960));

        // Create a layout.
        auto layout = VerticalLayout::create(context);
        layout->setSpacingRole(SizeRole::None);
        layout->setStretch(Stretch::Expanding);
        window->setWidget(layout);

        // Create a stack of labels.
        auto stackLayout = StackLayout::create(context, layout);
        stackLayout->setStretch(Stretch::Expanding);
        auto label = Label::create(context, "One", stackLayout);
        FontInfo fontInfo;
        fontInfo.size = 64;
        label->setFontInfo(fontInfo);
        label->setAlign(HAlign::Center, VAlign::Center);
        label = Label::create(context, "Two", stackLayout);
        label->setFontInfo(fontInfo);
        label->setAlign(HAlign::Center, VAlign::Center);
        label = Label::create(context, "Three", stackLayout);
        label->setFontInfo(fontInfo);
        label->setAlign(HAlign::Center, VAlign::Center);
        label = Label::create(context, "Four", stackLayout);
        label->setFontInfo(fontInfo);
        label->setAlign(HAlign::Center, VAlign::Center);

        // Create buttons to change the current label.
        Divider::create(context, Orientation::Vertical, layout);
        auto hLayout = HorizontalLayout::create(context, layout);
        hLayout->setMarginRole(SizeRole::Margin);
        
        auto nextButton = PushButton::create(context, "Next", hLayout);
        nextButton->setClickedCallback(
            [stackLayout]
            {
                stackLayout->nextIndex();
            });
        auto hasNextObserver = ValueObserver<bool>::create(
            stackLayout->observeHasNextIndex(),
            [nextButton](bool value)
            {
                nextButton->setEnabled(value);
            });

        auto prevButton = PushButton::create(context, "Previous", hLayout);
        prevButton->setClickedCallback(
            [stackLayout]
            {
                stackLayout->prevIndex();
            });
        auto hasPrevObserver = ValueObserver<bool>::create(
            stackLayout->observeHasPrevIndex(),
            [prevButton](bool value)
            {
                prevButton->setEnabled(value);
            });

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

