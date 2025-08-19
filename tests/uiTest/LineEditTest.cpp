// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/LineEditTest.h>

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/LineEdit.h>
#include <feather-tk/ui/RowLayout.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        LineEditTest::LineEditTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::LineEditTest")
        {}

        LineEditTest::~LineEditTest()
        {}

        std::shared_ptr<LineEditTest> LineEditTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<LineEditTest>(new LineEditTest(context));
        }
                
        void LineEditTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("LineEditTest");
                auto app = App::create(
                    context,
                    argv,
                    "LineEditTest",
                    "Line edit test.");
                auto window = Window::create(context, "LineEditTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto edit = LineEdit::create(context, layout);
                std::string text;
                edit->setTextCallback(
                    [&text](const std::string& value)
                    {
                        text = value;
                    });
                std::string textChanged;
                edit->setTextChangedCallback(
                    [&textChanged](const std::string& value)
                    {
                        textChanged = value;
                    });
                edit->setText("Test");
                edit->setText("Test");
                FEATHER_TK_ASSERT("Test" == edit->getText());
                edit->clearText();
                FEATHER_TK_ASSERT(edit->getText().empty());
                edit->setFormat("00.00");
                edit->setFormat("00.00");
                FEATHER_TK_ASSERT("00.00" == edit->getFormat());
                edit->setFormat("");
                edit->setFontRole(FontRole::Mono);
                edit->setFontRole(FontRole::Mono);
                FEATHER_TK_ASSERT(FontRole::Mono == edit->getFontRole());
                edit->setFontRole(FontRole::Label);

                edit->takeKeyFocus();
                app->tick();
                edit->hide();
                app->tick();
                edit->show();
                app->tick();
                FEATHER_TK_ASSERT(!edit->hasKeyFocus());

                edit->takeKeyFocus();
                app->tick();
                edit->setEnabled(false);
                app->tick();
                edit->setEnabled(true);
                app->tick();
                FEATHER_TK_ASSERT(!edit->hasKeyFocus());
            }
        }
    }
}

