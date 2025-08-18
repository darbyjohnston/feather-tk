// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/DoubleEditTest.h>

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/DoubleEdit.h>
#include <feather-tk/ui/RowLayout.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        DoubleEditTest::DoubleEditTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::DoubleEditTest")
        {}

        DoubleEditTest::~DoubleEditTest()
        {}

        std::shared_ptr<DoubleEditTest> DoubleEditTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<DoubleEditTest>(new DoubleEditTest(context));
        }
                
        void DoubleEditTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("DoubleEditTest");
                auto app = App::create(
                    context,
                    argv,
                    "DoubleEditTest",
                    "Double edit test.");
                auto window = Window::create(context, app, "DoubleEditTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto edit = DoubleEdit::create(context, layout);
                FEATHER_TK_ASSERT(edit->getModel());
                double value = 0.0;
                edit->setCallback([&value](double v) { value = v; });
                edit->setValue(0.9);
                app->tick();
                FEATHER_TK_ASSERT(0.9 == edit->getValue());
                FEATHER_TK_ASSERT(0.9 == value);
                edit->setRange(0.0, 0.5);
                app->tick();
                FEATHER_TK_ASSERT(RangeD(0.0, 0.5) == edit->getRange());
                FEATHER_TK_ASSERT(0.5 == value);
                edit->setStep(0.2);
                FEATHER_TK_ASSERT(0.2 == edit->getStep());
                edit->setLargeStep(0.3);
                FEATHER_TK_ASSERT(0.3 == edit->getLargeStep());
                edit->setPrecision(3);
                edit->setPrecision(3);
                FEATHER_TK_ASSERT(3 == edit->getPrecision());
                edit->setPrecision(2);
                edit->setFontRole(FontRole::Label);
                FEATHER_TK_ASSERT(FontRole::Label == edit->getFontRole());
                edit->setFontRole(FontRole::Mono);
            }
        }
    }
}

