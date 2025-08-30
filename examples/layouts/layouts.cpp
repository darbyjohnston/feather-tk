// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/FormLayout.h>
#include <feather-tk/ui/GridLayout.h>
#include <feather-tk/ui/GroupBox.h>
#include <feather-tk/ui/IntEdit.h>
#include <feather-tk/ui/IntEditSlider.h>
#include <feather-tk/ui/Label.h>
#include <feather-tk/ui/MainWindow.h>
#include <feather-tk/ui/RowLayout.h>
#include <feather-tk/ui/ScrollWidget.h>

#include <feather-tk/core/Format.h>

using namespace ftk;

FTK_MAIN()
{
    try
    {
        // Create the context and application.
        auto context = Context::create();
        auto app = App::create(context, argc, argv, "layouts", "Layouts example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create a window.
        auto window = MainWindow::create(
            context,
            app,
            "layouts",
            Size2I(1280, 960));

        // Create a layout.
        auto layout = VerticalLayout::create(context);
        layout->setMarginRole(SizeRole::Margin);
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Both);
        scrollWidget->setBorder(false);
        scrollWidget->setWidget(layout);
        scrollWidget->setVStretch(Stretch::Expanding);
        window->setWidget(scrollWidget);

        // Create row layouts.
        auto groupBox = GroupBox::create(context, "Row Layouts", layout);
        auto groupLayout = HorizontalLayout::create(context, groupBox);
        auto hLayout = HorizontalLayout::create(context, groupLayout);
        auto label = Label::create(context, "One", hLayout);
        label = Label::create(context, "Two", hLayout);
        hLayout->addSpacer();
        label = Label::create(context, "Three", hLayout);
        auto vLayout = VerticalLayout::create(context, groupLayout);
        label = Label::create(context, "One", vLayout);
        label = Label::create(context, "Two", vLayout);
        vLayout->addSpacer();
        label = Label::create(context, "Three", vLayout);

        // Create grid layouts.
        groupBox = GroupBox::create(context, "Grid Layouts", layout);
        groupLayout = HorizontalLayout::create(context, groupBox);
        auto gridLayout = GridLayout::create(context, groupLayout);
        label = Label::create(context, "One", gridLayout);
        gridLayout->setGridPos(label, 0, 0);
        label = Label::create(context, "Two", gridLayout);
        gridLayout->setGridPos(label, 0, 1);
        label = Label::create(context, "Three", gridLayout);
        gridLayout->setGridPos(label, 1, 0);
        label = Label::create(context, "Four", gridLayout);
        gridLayout->setGridPos(label, 1, 1);

        // Create form layouts.
        groupBox = GroupBox::create(context, "Form Layouts", layout);
        groupLayout = HorizontalLayout::create(context, groupBox);
        auto formLayout = FormLayout::create(context, groupLayout);
        formLayout->setHStretch(Stretch::Expanding);
        formLayout->addRow("One:", IntEditSlider::create(context));
        formLayout->addRow("Two:", IntEditSlider::create(context));
        formLayout->addSpacer();
        formLayout->addRow("Three:", IntEdit::create(context));

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

