// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/ProgressDialogTest.h>

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/ProgressDialog.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        ProgressDialogTest::ProgressDialogTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::ProgressDialogTest")
        {}

        ProgressDialogTest::~ProgressDialogTest()
        {}

        std::shared_ptr<ProgressDialogTest> ProgressDialogTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ProgressDialogTest>(new ProgressDialogTest(context));
        }
                
        void ProgressDialogTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("ProgressDialogTest");
                auto app = App::create(
                    context,
                    argv,
                    "ProgressDialogTest",
                    "Progress dialog test.");
                auto window = Window::create(context, app, "ProgressDialogTest");
                app->addWindow(window);
                window->show();
                app->tick();
            }
        }
    }
}

