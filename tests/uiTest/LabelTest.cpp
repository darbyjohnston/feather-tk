// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/LabelTest.h>

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/Label.h>
#include <feather-tk/ui/RowLayout.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        LabelTest::LabelTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::LabelTest")
        {}

        LabelTest::~LabelTest()
        {}

        std::shared_ptr<LabelTest> LabelTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<LabelTest>(new LabelTest(context));
        }
                
        void LabelTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("LabelTest");
                auto app = App::create(
                    context,
                    argv,
                    "LabelTest",
                    "Label test.");
                auto window = Window::create(context, "LabelTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto label = Label::create(context, layout);
                label->setText("Test");
                label->setText("Test");
                FEATHER_TK_ASSERT("Test" == label->getText());
                label->setTextRole(ColorRole::Red);
                label->setTextRole(ColorRole::Red);
                FEATHER_TK_ASSERT(ColorRole::Red == label->getTextRole());
                label->setMarginRole(SizeRole::Margin);
                label->setMarginRole(SizeRole::Margin);
                FEATHER_TK_ASSERT(SizeRole::Margin == label->getHMarginRole());
                FEATHER_TK_ASSERT(SizeRole::Margin == label->getVMarginRole());
                label->setMarginRole(SizeRole::Margin, SizeRole::None);
                label->setMarginRole(SizeRole::Margin, SizeRole::None);
                FEATHER_TK_ASSERT(SizeRole::Margin == label->getHMarginRole());
                FEATHER_TK_ASSERT(SizeRole::None == label->getVMarginRole());
                label->setHMarginRole(SizeRole::None);
                label->setHMarginRole(SizeRole::None);
                FEATHER_TK_ASSERT(SizeRole::None == label->getHMarginRole());
                label->setVMarginRole(SizeRole::Margin);
                label->setVMarginRole(SizeRole::Margin);
                FEATHER_TK_ASSERT(SizeRole::Margin == label->getVMarginRole());
                label->setFontRole(FontRole::Mono);
                label->setFontRole(FontRole::Mono);
                FEATHER_TK_ASSERT(FontRole::Mono == label->getFontRole());

                label->setEnabled(false);
                app->tick();
                label->setEnabled(true);
                app->tick();

                label->hide();
                app->tick();
                label->show();
                app->tick();
            }
        }
    }
}

