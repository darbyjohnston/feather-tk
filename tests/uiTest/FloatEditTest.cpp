// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/FloatEditTest.h>

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/FloatEdit.h>
#include <feather-tk/ui/RowLayout.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        FloatEditTest::FloatEditTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::FloatEditTest")
        {}

        FloatEditTest::~FloatEditTest()
        {}

        std::shared_ptr<FloatEditTest> FloatEditTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FloatEditTest>(new FloatEditTest(context));
        }

        void FloatEditTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("FloatEditTest");
                auto app = App::create(
                    context,
                    argv,
                    "FloatEditTest",
                    "Float edit test.");
                auto window = Window::create(context, "FloatEditTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto edit = FloatEdit::create(context, layout);
                FEATHER_TK_ASSERT(edit->getModel());
                float value = 0.F;
                edit->setCallback([&value](float v) { value = v; });
                edit->setValue(.9F);
                app->tick();
                FEATHER_TK_ASSERT(.9F == edit->getValue());
                FEATHER_TK_ASSERT(.9F == value);
                edit->setRange(0.F, .5F);
                app->tick();
                FEATHER_TK_ASSERT(RangeF(0.F, .5F) == edit->getRange());
                FEATHER_TK_ASSERT(.5F == value);
                edit->setStep(.2F);
                FEATHER_TK_ASSERT(.2F == edit->getStep());
                edit->setLargeStep(.3F);
                FEATHER_TK_ASSERT(.3F == edit->getLargeStep());
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

