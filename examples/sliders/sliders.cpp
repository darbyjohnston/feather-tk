// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/GroupBox.h>
#include <feather-tk/ui/DoubleEditSlider.h>
#include <feather-tk/ui/FloatEditSlider.h>
#include <feather-tk/ui/IntEditSlider.h>
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
        auto app = App::create(context, argc, argv, "sliders", "Sliders example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create thae window.
        auto window = MainWindow::create(
            context,
            app,
            "sliders",
            Size2I(1280, 960));

        // Create a layout.
        auto layout = VerticalLayout::create(context);
        layout->setMarginRole(SizeRole::Margin);
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Both);
        scrollWidget->setBorder(false);
        scrollWidget->setVStretch(Stretch::Expanding);
        scrollWidget->setWidget(layout);
        window->setWidget(scrollWidget);

        // Create integer sliders.
        auto groupBox = GroupBox::create(context, "Integer Sliders", layout);
        auto vLayout = VerticalLayout::create(context, groupBox);
        auto intEditSlider = IntEditSlider::create(context, vLayout);
        intEditSlider->setCallback(
            [](int value)
            {
                std::cout << Format("Int: {0}").arg(value) << std::endl;
            });
        intEditSlider = IntEditSlider::create(context, vLayout);
        intEditSlider->setRange(100, 200);
        intEditSlider->setDefaultValue(100);
        intEditSlider->setCallback(
            [](int value)
            {
                std::cout << Format("Int: {0}").arg(value) << std::endl;
            });
        intEditSlider = IntEditSlider::create(context, vLayout);
        intEditSlider->setRange(-100, 100);
        intEditSlider->setDefaultValue(-100);
        intEditSlider->setCallback(
            [](int value)
            {
                std::cout << Format("Int: {0}").arg(value) << std::endl;
            });

        // Create float sliders.
        groupBox = GroupBox::create(context, "Float Sliders", layout);
        vLayout = VerticalLayout::create(context, groupBox);
        auto floatEditSlider = FloatEditSlider::create(context, vLayout);
        floatEditSlider->setCallback(
            [](float value)
            {
                std::cout << Format("Float: {0}").arg(value) << std::endl;
            });
        floatEditSlider = FloatEditSlider::create(context, vLayout);
        floatEditSlider->setRange(100.F, 200.F);
        floatEditSlider->setDefaultValue(100.F);
        floatEditSlider->setStep(1.F);
        floatEditSlider->setLargeStep(10.F);
        floatEditSlider->setCallback(
            [](float value)
            {
                std::cout << Format("Float: {0}").arg(value) << std::endl;
            });
        floatEditSlider = FloatEditSlider::create(context, vLayout);
        floatEditSlider->setRange(-100.F, 100.F);
        floatEditSlider->setDefaultValue(-100.F);
        floatEditSlider->setStep(1.F);
        floatEditSlider->setLargeStep(10.F);
        floatEditSlider->setCallback(
            [](float value)
            {
                std::cout << Format("Float: {0}").arg(value) << std::endl;
            });

        // Create double sliders.
        groupBox = GroupBox::create(context, "Double Sliders", layout);
        vLayout = VerticalLayout::create(context, groupBox);
        auto doubleEditSlider = DoubleEditSlider::create(context, vLayout);
        doubleEditSlider->setCallback(
            [](double value)
            {
                std::cout << Format("Double: {0}").arg(value) << std::endl;
            });
        doubleEditSlider = DoubleEditSlider::create(context, vLayout);
        doubleEditSlider->setRange(100.0, 200.0);
        doubleEditSlider->setDefaultValue(100.0);
        doubleEditSlider->setStep(1.F);
        doubleEditSlider->setLargeStep(10.F);
        doubleEditSlider->setCallback(
            [](double value)
            {
                std::cout << Format("Double: {0}").arg(value) << std::endl;
            });
        doubleEditSlider = DoubleEditSlider::create(context, vLayout);
        doubleEditSlider->setRange(-100.0, 100.0);
        doubleEditSlider->setDefaultValue(-100.0);
        doubleEditSlider->setStep(1.F);
        doubleEditSlider->setLargeStep(10.F);
        doubleEditSlider->setCallback(
            [](double value)
            {
                std::cout << Format("Double: {0}").arg(value) << std::endl;
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

