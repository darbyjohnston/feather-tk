// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/Action.h>
#include <feather-tk/ui/ComboBox.h>
#include <feather-tk/ui/ColorSwatch.h>
#include <feather-tk/ui/Divider.h>
#include <feather-tk/ui/GroupBox.h>
#include <feather-tk/ui/MainWindow.h>
#include <feather-tk/ui/MenuBar.h>
#include <feather-tk/ui/RowLayout.h>
#include <feather-tk/ui/ScrollWidget.h>

using namespace feather_tk;

FEATHER_TK_MAIN()
{
    try
    {
        // Create the context and application.
        auto context = Context::create();
        auto app = App::create(context, argc, argv, "popups", "Popups example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create a window.
        auto window = MainWindow::create(
            context,
            app,
            "popups",
            Size2I(1280, 960));

        // Create menus.
        auto menu = Menu::create(context);
        menu->addAction(Action::create(
            "Action 1",
            [] { std::cout << "Action 1" << std::endl; }));
        menu->addAction(Action::create(
            "Action 2",
            "FileOpen",
            [] { std::cout << "Action 2" << std::endl; }));
        menu->addDivider();
        menu->addAction(Action::create(
            "Action 3",
            Key::_3,
            static_cast<int>(KeyModifier::Control),
            [] { std::cout << "Action 3" << std::endl; }));
        menu->addDivider();
        menu->addAction(Action::create(
            "Action 4",
            "FileClose",
            Key::_4,
            static_cast<int>(KeyModifier::Control),
            [] { std::cout << "Action 4" << std::endl; }));
        window->getMenuBar()->addMenu("Menu 1", menu);
        menu = Menu::create(context);
        menu->addAction(Action::create(
            "Action 5",
            [](bool value) { std::cout << "Action 5: " << value << std::endl; }));
        menu->addAction(Action::create(
            "Action 6",
            "Next",
            [](bool value) { std::cout << "Action 6: " << value << std::endl; }));
        menu->addAction(Action::create(
            "Action 7",
            Key::_7,
            static_cast<int>(KeyModifier::Control),
            [](bool value) { std::cout << "Action 7: " << value << std::endl; }));
        menu->addAction(Action::create(
            "Action 8",
            "Prev",
            Key::_8,
            static_cast<int>(KeyModifier::Control),
            [](bool value) { std::cout << "Action 8: " << value << std::endl; }));
        window->getMenuBar()->addMenu("Menu 2", menu);

        menu = Menu::create(context);
        menu->addAction(Action::create(
            "Action 9",
            [] { std::cout << "Action 9" << std::endl; }));
        auto subMenu = menu->addSubMenu("Sub Menu 1");
        subMenu->addAction(Action::create(
            "Action 10",
            [] { std::cout << "Action 10" << std::endl; }));
        subMenu = menu->addSubMenu("Sub Menu 2");
        subMenu->addAction(Action::create(
            "Action 11",
            [] { std::cout << "Action 11" << std::endl; }));
        subMenu->addAction(Action::create(
            "Action 12",
            [] { std::cout << "Action 12" << std::endl; }));
        subMenu = menu->addSubMenu("Sub Menu 3");
        subMenu->addAction(Action::create(
            "Action 13",
            [] { std::cout << "Action 13" << std::endl; }));
        subMenu->addAction(Action::create(
            "Action 14",
            [] { std::cout << "Action 14" << std::endl; }));
        subMenu->addAction(Action::create(
            "Action 15",
            [] { std::cout << "Action 15" << std::endl; }));
        subMenu = menu->addSubMenu("Sub Menu 4");
        menu->addAction(Action::create(
            "Action 16",
            [] { std::cout << "Action 16" << std::endl; }));
        window->getMenuBar()->addMenu("Menu 3", menu);

        menu = Menu::create(context);
        window->getMenuBar()->addMenu("Menu 4", menu);

        // Create a layout.
        auto layout = VerticalLayout::create(context);
        layout->setMarginRole(SizeRole::Margin);
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Both);
        scrollWidget->setBorder(false);
        scrollWidget->setStretch(Stretch::Expanding);
        scrollWidget->setWidget(layout);
        window->setWidget(scrollWidget);

        // Create combo boxes.
        auto groupBox = GroupBox::create(context, "Combo Boxes", layout);
        auto vLayout = VerticalLayout::create(context, groupBox);
        auto comboBox = ComboBox::create(context, vLayout);
        comboBox->setItems(
            {
                ComboBoxItem("Stop", "PlaybackStop"),
                ComboBoxItem("Forward", "PlaybackForward"),
                ComboBoxItem("Reverse", "PlaybackReverse")
            });
        comboBox->setTooltip("Playback");
        comboBox = ComboBox::create(context, getImageTypeLabels(), vLayout);
        comboBox->setTooltip("Image types");
        comboBox = ComboBox::create(context, vLayout);

        // Create color swatches.
        groupBox = GroupBox::create(context, "Color Popups", layout);
        auto hLayout = HorizontalLayout::create(context, groupBox);
        const std::vector<Color4F> colors =
        {
            Color4F(1.F, .5F, .5F),
            Color4F(.5F, 1.F, .5F),
            Color4F(.5F, .5F, 1.F),
            Color4F(1.F, 1.F, .5F),
            Color4F(.5F, 1.F, 1.F),
            Color4F(1.F, .5F, 1.F)
        };
        for (const auto& color : colors)
        {
            auto colorSwatch = ColorSwatch::create(context, hLayout);
            colorSwatch->setColor(color);
            colorSwatch->setEditable(true);
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

