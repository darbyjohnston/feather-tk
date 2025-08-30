// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/ListWidget.h>
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
        auto app = App::create(context, argc, argv, "lists", "Lists example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create a window.
        auto window = MainWindow::create(
            context,
            app,
            "lists",
            Size2I(1280, 960));

        // Create a layout.
        auto layout = VerticalLayout::create(context);
        layout->setMarginRole(SizeRole::Margin);
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Both);
        scrollWidget->setBorder(false);
        scrollWidget->setWidget(layout);
        scrollWidget->setVStretch(Stretch::Expanding);
        window->setWidget(scrollWidget);

        // Create a clickable list widget.
        auto listWidget = ListWidget::create(context, ButtonGroupType::Click, layout);
        std::vector<std::string> items;
        for (size_t i = 0; i < 100; ++i)
        {
            items.push_back(Format("Click {0}").arg(i));
        }
        listWidget->setItems(items);
        listWidget->setCallback(
            [](int index, bool)
            {
                std::cout << "Click: " << index << std::endl;
            });

        // Create a checkable list widget.
        listWidget = ListWidget::create(context, ButtonGroupType::Check, layout);
        items.clear();
        for (size_t i = 0; i < 100; ++i)
        {
            items.push_back(Format("Check {0}").arg(i));
        }
        listWidget->setItems(items);
        listWidget->setChecked(0);
        listWidget->setChecked(1);
        listWidget->setChecked(2);
        listWidget->setChecked(4);
        listWidget->setCallback(
            [](int index, bool value)
            {
                std::cout << "Check: " << index << std::endl;
            });
        listWidget->setCurrent(static_cast<int>(items.size()) - 1);

        // Create a radio button list widget.
        listWidget = ListWidget::create(context, ButtonGroupType::Radio, layout);
        items.clear();
        for (size_t i = 0; i < 100; ++i)
        {
            items.push_back(Format("Radio {0}").arg(i));
        }
        listWidget->setItems(items);
        listWidget->setChecked(0);
        listWidget->setCallback(
            [](int index, bool)
            {
                std::cout << "Radio: " << index << std::endl;
            });

        // Create a toggle button list widget.
        listWidget = ListWidget::create(context, ButtonGroupType::Toggle, layout);
        items.clear();
        for (size_t i = 0; i < 100; ++i)
        {
            items.push_back(Format("Toggle {0}").arg(i));
        }
        listWidget->setItems(items);
        listWidget->setChecked(0);
        listWidget->setCallback(
            [](int index, bool)
            {
                std::cout << "Toggle: " << index << std::endl;
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

