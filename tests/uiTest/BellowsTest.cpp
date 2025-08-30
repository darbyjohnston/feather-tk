// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/BellowsTest.h>

#include <ftk/ui/App.h>
#include <ftk/ui/Bellows.h>
#include <ftk/ui/Label.h>
#include <ftk/ui/RowLayout.h>
#include <ftk/ui/Window.h>

#include <ftk/core/Assert.h>
#include <ftk/core/Format.h>

namespace ftk
{
    namespace ui_test
    {
        BellowsTest::BellowsTest(const std::shared_ptr<Context>& context) :
            ITest(context, "ftk::ui_test::BellowsTest")
        {}

        BellowsTest::~BellowsTest()
        {}

        std::shared_ptr<BellowsTest> BellowsTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<BellowsTest>(new BellowsTest(context));
        }
                
        void BellowsTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("BellowsTest");
                auto app = App::create(
                    context,
                    argv,
                    "BellowsTest",
                    "Bellows test.");
                auto window = Window::create(context, "BellowsTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto bellows = Bellows::create(context, "Bellows", layout);
                bellows->setText("Test");
                FTK_ASSERT("Test" == bellows->getText());
                auto label = Label::create(context, "Label");
                bellows->setWidget(label);
                bellows->setWidget(label);
                FTK_ASSERT(label == bellows->getWidget());
                bellows->setOpen(true);
                bellows->setOpen(true);
                FTK_ASSERT(bellows->isOpen());
                bellows->setOpen(false);

                bellows->hide();
                app->tick();
                bellows->show();
                app->tick();
            }
        }
    }
}

