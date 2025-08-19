// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/IntEditSliderTest.h>

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/IntEditSlider.h>
#include <feather-tk/ui/RowLayout.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        IntEditSliderTest::IntEditSliderTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::IntEditSliderTest")
        {}

        IntEditSliderTest::~IntEditSliderTest()
        {}

        std::shared_ptr<IntEditSliderTest> IntEditSliderTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<IntEditSliderTest>(new IntEditSliderTest(context));
        }
                
        void IntEditSliderTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("IntEditSliderTest");
                auto app = App::create(
                    context,
                    argv,
                    "IntEditSliderTest",
                    "Integer edit slider test.");
                auto window = Window::create(context, "IntEditSliderTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto slider = IntEditSlider::create(context, layout);
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
                slider->setDefaultValue(0);
                FEATHER_TK_ASSERT(0 == slider->getDefaultValue());
                slider->setFontRole(FontRole::Label);
                FEATHER_TK_ASSERT(FontRole::Label == slider->getFontRole());
                slider->setFontRole(FontRole::Mono);
            }
        }
    }
}

