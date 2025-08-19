// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/DoubleEditSliderTest.h>

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/DoubleEditSlider.h>
#include <feather-tk/ui/RowLayout.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        DoubleEditSliderTest::DoubleEditSliderTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::DoubleEditSliderTest")
        {}

        DoubleEditSliderTest::~DoubleEditSliderTest()
        {}

        std::shared_ptr<DoubleEditSliderTest> DoubleEditSliderTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<DoubleEditSliderTest>(new DoubleEditSliderTest(context));
        }
                
        void DoubleEditSliderTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("DoubleEditSliderTest");
                auto app = App::create(
                    context,
                    argv,
                    "DoubleEditSliderTest",
                    "Double edit slider test.");
                auto window = Window::create(context, "DoubleEditSliderTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto slider = DoubleEditSlider::create(context, layout);
                FEATHER_TK_ASSERT(slider->getModel());
                double value = 0.0;
                slider->setCallback([&value](double v) { value = v; });
                slider->setValue(0.9);
                app->tick();
                FEATHER_TK_ASSERT(0.9 == slider->getValue());
                FEATHER_TK_ASSERT(0.9 == value);
                slider->setRange(0.0, 0.5);
                app->tick();
                FEATHER_TK_ASSERT(RangeD(0.0, 0.5) == slider->getRange());
                FEATHER_TK_ASSERT(0.5 == value);
                slider->setStep(0.2);
                FEATHER_TK_ASSERT(0.2 == slider->getStep());
                slider->setLargeStep(0.3);
                FEATHER_TK_ASSERT(0.3 == slider->getLargeStep());
                slider->setPrecision(3);
                FEATHER_TK_ASSERT(3 == slider->getPrecision());
                slider->setPrecision(2);
                slider->setDefaultValue(0.0);
                FEATHER_TK_ASSERT(0.0 == slider->getDefaultValue());
                slider->setFontRole(FontRole::Label);
                FEATHER_TK_ASSERT(FontRole::Label == slider->getFontRole());
                slider->setFontRole(FontRole::Mono);
            }
        }
    }
}

