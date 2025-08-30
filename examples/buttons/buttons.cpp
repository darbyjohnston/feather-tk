// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/ui/App.h>
#include <ftk/ui/ButtonGroup.h>
#include <ftk/ui/CheckBox.h>
#include <ftk/ui/GroupBox.h>
#include <ftk/ui/MainWindow.h>
#include <ftk/ui/PushButton.h>
#include <ftk/ui/RadioButton.h>
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
        auto app = App::create(context, argc, argv, "buttons", "Buttons example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create a window.
        auto window = MainWindow::create(
            context,
            app,
            "buttons",
            Size2I(1280, 960));

        // Create a layout.
        auto layout = VerticalLayout::create(context);
        layout->setMarginRole(SizeRole::Margin);
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Both);
        scrollWidget->setBorder(false);
        scrollWidget->setWidget(layout);
        scrollWidget->setVStretch(Stretch::Expanding);
        window->setWidget(scrollWidget);

        // Create push buttons.
        auto groupBox = GroupBox::create(context, "Push Buttons", layout);
        auto hLayout = HorizontalLayout::create(context, groupBox);
        hLayout->setSpacingRole(SizeRole::SpacingSmall);
        auto pushButton = PushButton::create(context, "Click", hLayout);
        pushButton->setClickedCallback(
            []
            {
                std::cout << "Click" << std::endl;
            });
        pushButton = PushButton::create(context, "Text", hLayout);
        pushButton->setIcon("Settings");
        pushButton = PushButton::create(context, "Disabled", hLayout);
        pushButton->setEnabled(false);

        // Create tool buttons.
        groupBox = GroupBox::create(context, "Tool Buttons", layout);
        hLayout = HorizontalLayout::create(context, groupBox);
        hLayout->setSpacingRole(SizeRole::SpacingSmall);
        auto toolButtonGroup = ButtonGroup::create(context, ButtonGroupType::Radio);
        toolButtonGroup->setCheckedCallback(
            [](int index, bool value)
            {
                std::cout << Format("Tool {0}").arg(index) << std::endl;
            });
        const std::vector<std::string> toolIcons =
        {
            "PlaybackReverse",
            "PlaybackStop",
            "PlaybackForward"
        };
        const std::vector<std::string> toolTooltips =
        {
            "Reverse playback",
            "Stop playback",
            "Forward playback"
        };
        auto hLayout2 = HorizontalLayout::create(context, hLayout);
        hLayout2->setSpacingRole(SizeRole::SpacingTool);
        for (size_t i = 0; i < 3; ++i)
        {
            auto toolButton = ToolButton::create(context, hLayout2);
            toolButton->setCheckable(true);
            toolButton->setChecked(0 == i);
            toolButton->setIcon(toolIcons[i]);
            toolButton->setTooltip(toolTooltips[i]);
            toolButtonGroup->addButton(toolButton);
        }
        auto playStopButton = ToolButton::create(context, hLayout);
        playStopButton->setIcon("PlaybackStop");
        playStopButton->setCheckedIcon("PlaybackForward");
        playStopButton->setCheckable(true);
        auto toolButton = ToolButton::create(context, "Text", hLayout);
        toolButton = ToolButton::create(context, "Text", hLayout);
        toolButton->setIcon("Settings");
        toolButton = ToolButton::create(context, "Disabled", hLayout);
        toolButton->setEnabled(false);
        toolButtonGroup->addButton(toolButton);

        // Create check boxes.
        groupBox = GroupBox::create(context, "Check Boxes", layout);
        auto vLayout = VerticalLayout::create(context, groupBox);
        vLayout->setSpacingRole(SizeRole::SpacingSmall);
        auto checkBox = CheckBox::create(context, "Check", vLayout);
        checkBox->setCheckedCallback(
            [](bool value)
            {
                std::cout << Format("Checked: {0}").arg(value) << std::endl;
            });
        checkBox = CheckBox::create(context, "Disabled", vLayout);
        checkBox->setEnabled(false);

        // Create radio buttons.
        groupBox = GroupBox::create(context, "Radio Buttons", layout);
        vLayout = VerticalLayout::create(context, groupBox);
        vLayout->setSpacingRole(SizeRole::SpacingSmall);
        auto radioButtonGroup = ButtonGroup::create(context, ButtonGroupType::Radio);
        radioButtonGroup->setCheckedCallback(
            [](int index, bool value)
            {
                std::cout << Format("Radio {0}").arg(index) << std::endl;
            });
        for (size_t i = 0; i < 3; ++i)
        {
            auto radioButton = RadioButton::create(context, vLayout);
            radioButton->setText(Format("Radio {0}").arg(i));
            radioButton->setChecked(0 == i);
            radioButtonGroup->addButton(radioButton);
        }
        auto radioButton = RadioButton::create(context, "Disabled", vLayout);
        radioButton->setEnabled(false);

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

