// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/IntSliderTest.h>

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/IntSlider.h>
#include <feather-tk/ui/RowLayout.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        IntSliderTest::IntSliderTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::IntSliderTest")
        {}

        IntSliderTest::~IntSliderTest()
        {}

        std::shared_ptr<IntSliderTest> IntSliderTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<IntSliderTest>(new IntSliderTest(context));
        }
                
        void IntSliderTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("IntSliderTest");
                auto app = App::create(
                    context,
                    argv,
                    "IntSliderTest",
                    "Integer slider test.");
                auto window = Window::create(context, app, "IntSliderTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto slider = IntSlider::create(context, layout);
                FEATHER_TK_ASSERT(slider->getModel());
                int value = 0;
                slider->setCallback([&value](int v) { value = v; });
                slider->setValue(11);
                app->tick();
                FEATHER_TK_ASSERT(11 == slider->getValue());
                FEATHER_TK_ASSERT(11 == value);
                slider->setRange(0, 10);
                app->tick();
                FEATHER_TK_ASSERT(RangeI(0, 10) == slider->getRange());
                FEATHER_TK_ASSERT(10 == value);
                slider->setStep(2);
                FEATHER_TK_ASSERT(2 == slider->getStep());
                slider->setLargeStep(3);
                FEATHER_TK_ASSERT(3 == slider->getLargeStep());
            }
        }
    }
}

