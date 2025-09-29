// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <UiTest/FloatEditSliderTest.h>

#include <ftk/Ui/App.h>
#include <ftk/Ui/FloatEditSlider.h>
#include <ftk/Ui/RowLayout.h>
#include <ftk/Ui/Window.h>

#include <ftk/Core/Assert.h>
#include <ftk/Core/Format.h>

namespace ftk
{
    namespace ui_test
    {
        FloatEditSliderTest::FloatEditSliderTest(const std::shared_ptr<Context>& context) :
            ITest(context, "ftk::ui_test::FloatEditSliderTest")
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
                auto window = Window::create(context, "FloatEditSliderTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto slider = FloatEditSlider::create(context, layout);
                FTK_ASSERT(slider->getModel());
                float value = 0.F;
                slider->setCallback([&value](float v) { value = v; });
                slider->setValue(.9F);
                app->tick();
                FTK_ASSERT(.9F == slider->getValue());
                FTK_ASSERT(.9F == value);
                slider->setRange(0.F, .5F);
                app->tick();
                FTK_ASSERT(RangeF(0.F, .5F) == slider->getRange());
                FTK_ASSERT(.5F == value);
                slider->setStep(.2F);
                FTK_ASSERT(.2F == slider->getStep());
                slider->setLargeStep(.3F);
                FTK_ASSERT(.3F == slider->getLargeStep());
                slider->setPrecision(3);
                FTK_ASSERT(3 == slider->getPrecision());
                slider->setPrecision(2);
                slider->setDefaultValue(0.F);
                FTK_ASSERT(0.F == slider->getDefaultValue());
                slider->setFontRole(FontRole::Label);
                FTK_ASSERT(FontRole::Label == slider->getFontRole());
                slider->setFontRole(FontRole::Mono);
            }
        }
    }
}

