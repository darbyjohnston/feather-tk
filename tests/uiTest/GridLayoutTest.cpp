// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/GridLayoutTest.h>

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/Divider.h>
#include <feather-tk/ui/GridLayout.h>
#include <feather-tk/ui/Spacer.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        GridLayoutTest::GridLayoutTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::GridLayoutTest")
        {}

        GridLayoutTest::~GridLayoutTest()
        {}

        std::shared_ptr<GridLayoutTest> GridLayoutTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<GridLayoutTest>(new GridLayoutTest(context));
        }

        void GridLayoutTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("GridLayoutTest");
                auto app = App::create(
                    context,
                    argv,
                    "GridLayoutTest",
                    "Grid layout test.");
                auto window = Window::create(context, "GridLayoutTest");
                app->addWindow(window);
                window->show();
                app->tick();

                auto layout = GridLayout::create(context, window);
                layout->setSpacingRole(SizeRole::None);
                layout->setSpacingRole(SizeRole::None);
                layout->setSpacingRole(SizeRole::Spacing);
                FEATHER_TK_ASSERT(SizeRole::Spacing == layout->getSpacingRole());
                layout->setMarginRole(SizeRole::Margin);
                layout->setMarginRole(SizeRole::Margin);
                layout->setMarginRole(SizeRole::None);
                FEATHER_TK_ASSERT(SizeRole::None == layout->getMarginRole());

                auto spacer0 = Spacer::create(context, Orientation::Horizontal, layout);
                auto spacer1 = Spacer::create(context, Orientation::Horizontal, layout);
                auto spacer2 = Spacer::create(context, Orientation::Horizontal, layout);
                spacer2->setStretch(Stretch::Expanding);
                layout->setGridPos(spacer0, 0, 0);
                layout->setGridPos(spacer1, 0, 1);
                layout->setGridPos(spacer2, 1, 1);
                app->tick();

                spacer2->setParent(nullptr);
                app->tick();
            }
        }
    }
}

