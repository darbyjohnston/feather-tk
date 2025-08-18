// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/FloatEditSliderTest.h>

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/FloatEditSlider.h>
#include <feather-tk/ui/RowLayout.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        FloatEditSliderTest::FloatEditSliderTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::FloatEditSliderTest")
        {}

        FloatEditSliderTest::~FloatEditSliderTest()
        {}

        std::shared_ptr<FloatEditSliderTest> FloatEditSliderTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FloatEditSliderTest>(new FloatEditSliderTest(context));
        }

        void FloatEditSliderTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("FloatEditSliderTest");
                auto app = App::create(
                    context,
                    argv,
                    "FloatEditSliderTest",
                    "Float edit slider test.");
                auto window = Window::create(context, app, "FloatEditSliderTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto slider = FloatEditSlider::create(context, layout);
                FEATHER_TK_ASSERT(slider->getModel());
                float value = 0.F;
                slider->setCallback([&value](float v) { value = v; });
                slider->setValue(.9F);
                app->tick();
                FEATHER_TK_ASSERT(.9F == slider->getValue());
                FEATHER_TK_ASSERT(.9F == value);
                slider->setRange(0.F, .5F);
                app->tick();
                FEATHER_TK_ASSERT(RangeF(0.F, .5F) == slider->getRange());
                FEATHER_TK_ASSERT(.5F == value);
                slider->setStep(.2F);
                FEATHER_TK_ASSERT(.2F == slider->getStep());
                slider->setLargeStep(.3F);
                FEATHER_TK_ASSERT(.3F == slider->getLargeStep());
                slider->setPrecision(3);
                FEATHER_TK_ASSERT(3 == slider->getPrecision());
                slider->setPrecision(2);
                slider->setDefaultValue(0.F);
                FEATHER_TK_ASSERT(0.F == slider->getDefaultValue());
                slider->setFontRole(FontRole::Label);
                FEATHER_TK_ASSERT(FontRole::Label == slider->getFontRole());
                slider->setFontRole(FontRole::Mono);
            }
        }
    }
}

