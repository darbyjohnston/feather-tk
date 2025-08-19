// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/StackLayoutTest.h>

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/Divider.h>
#include <feather-tk/ui/StackLayout.h>
#include <feather-tk/ui/Spacer.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        StackLayoutTest::StackLayoutTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::StackLayoutTest")
        {}

        StackLayoutTest::~StackLayoutTest()
        {}

        std::shared_ptr<StackLayoutTest> StackLayoutTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<StackLayoutTest>(new StackLayoutTest(context));
        }

        void StackLayoutTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("StackLayoutTest");
                auto app = App::create(
                    context,
                    argv,
                    "StackLayoutTest",
                    "Stack layout test.");
                auto window = Window::create(context, "StackLayoutTest");
                app->addWindow(window);
                window->show();
                app->tick();

                auto layout = StackLayout::create(context, window);
                layout->setMarginRole(SizeRole::Margin);
                layout->setMarginRole(SizeRole::Margin);
                layout->setMarginRole(SizeRole::None);
                FEATHER_TK_ASSERT(SizeRole::None == layout->getMarginRole());

                auto spacer0 = Spacer::create(context, Orientation::Horizontal, layout);
                auto spacer1 = Spacer::create(context, Orientation::Horizontal, layout);
                auto spacer2 = Spacer::create(context, Orientation::Horizontal, layout);
                app->tick();
                FEATHER_TK_ASSERT(0 == layout->getCurrentIndex());
                FEATHER_TK_ASSERT(spacer0->isVisible());
                FEATHER_TK_ASSERT(!spacer1->isVisible());
                FEATHER_TK_ASSERT(!spacer2->isVisible());

                layout->setCurrentIndex(1);
                app->tick();
                FEATHER_TK_ASSERT(!spacer0->isVisible());
                FEATHER_TK_ASSERT(spacer1->isVisible());
                FEATHER_TK_ASSERT(!spacer2->isVisible());

                layout->setCurrentWidget(spacer2);
                app->tick();
                FEATHER_TK_ASSERT(2 == layout->getCurrentIndex());
                FEATHER_TK_ASSERT(!spacer0->isVisible());
                FEATHER_TK_ASSERT(!spacer1->isVisible());
                FEATHER_TK_ASSERT(spacer2->isVisible());

                spacer2->setParent(nullptr);
                app->tick();
                FEATHER_TK_ASSERT(1 == layout->getCurrentIndex());
                FEATHER_TK_ASSERT(!spacer0->isVisible());
                FEATHER_TK_ASSERT(spacer1->isVisible());
            }
        }
    }
}

