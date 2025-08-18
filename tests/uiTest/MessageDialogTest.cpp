// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/MessageDialogTest.h>

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/MessageDialog.h>
#include <feather-tk/ui/DialogSystem.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        MessageDialogTest::MessageDialogTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::MessageDialogTest")
        {}

        MessageDialogTest::~MessageDialogTest()
        {}

        std::shared_ptr<MessageDialogTest> MessageDialogTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<MessageDialogTest>(new MessageDialogTest(context));
        }
                
        void MessageDialogTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("MessageDialogTest");
                auto app = App::create(
                    context,
                    argv,
                    "MessageDialogTest",
                    "Message dialog test.");
                auto window = Window::create(context, app, "MessageDialogTest");
                app->addWindow(window);
                window->show();
                app->tick();
            }
        }
    }
}

