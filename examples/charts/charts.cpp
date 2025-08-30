// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/ui/App.h>
#include <ftk/ui/MainWindow.h>
#include <ftk/ui/PieChart.h>
#include <ftk/ui/RowLayout.h>
#include <ftk/ui/ScrollWidget.h>

using namespace ftk;

FTK_MAIN()
{
    try
    {
        // Create the context and application.
        auto context = Context::create();
        auto app = App::create(context, argc, argv, "charts", "Charts example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create a window.
        auto window = MainWindow::create(
            context,
            app,
            "charts",
            Size2I(1280, 960));

        // Create a layout.
        auto layout = VerticalLayout::create(context);
        layout->setMarginRole(SizeRole::Margin);
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Both);
        scrollWidget->setBorder(false);
        scrollWidget->setWidget(layout);
        scrollWidget->setVStretch(Stretch::Expanding);
        window->setWidget(scrollWidget);

        // Create pie charts.
        auto hLayout = HorizontalLayout::create(context, layout);
        auto pieChart = PieChart::create(context, hLayout);
        pieChart->setData(
            {
                PieChartData(100.F, Color4F(.8F, .2F, 0.F))
            });
        pieChart = PieChart::create(context, hLayout);
        pieChart->setData(
            {
                PieChartData(50.F, Color4F(.8F, .2F, 0.F)),
                PieChartData(50.F, Color4F(.9F, .7F, .1F))
            });
        pieChart = PieChart::create(context, hLayout);
        pieChart->setData(
            {
                PieChartData(40.F, Color4F(.8F, .2F, 0.F)),
                PieChartData(30.F, Color4F(.9F, .7F, .1F)),
                PieChartData(15.F, Color4F(0.F, .8F, .3F)),
                PieChartData(10.F, Color4F(.2F, .2F, .9F)),
                PieChartData(5.F, Color4F(.5F, .1F, .8F))
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

