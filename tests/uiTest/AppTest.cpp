// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/AppTest.h>

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/ui/PushButton.h>
#include <feather-tk/ui/RowLayout.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        AppTest::AppTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::AppTest")
        {}

        AppTest::~AppTest()
        {}

        std::shared_ptr<AppTest> AppTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<AppTest>(new AppTest(context));
        }
                
        void AppTest::run()
        {
            int r = 0;
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv = { "app", "-exit" };
                try
                {
                    auto app = App::create(
                        context,
                        argv,
                        "feather_tk::ui_test::App",
                        "Test UI application");
                    r = app->getExit();
                    if (0 == r)
                    {
                        auto window = Window::create(context, app, "feather_tk::ui_test::App");
                        auto layout = VerticalLayout::create(context, window);
                        auto button = PushButton::create(context, "Button", layout);
                        app->addWindow(window);
                        FEATHER_TK_ASSERT(app->getWindows().front() == window);
                        window->show();
                        window->setSize(Size2I(1920, 1080));

                        _print(Format("Window size: {0}").arg(window->getSize()));
                        _print(Format("Frame buffer size: {0}").
                            arg(window->getFrameBufferSize()));
                        _print(Format("Display scale: {0}").
                            arg(window->getDisplayScale()));

                        app->run();
                        app->exit();
                        window->hide();
                        app->removeWindow(window);
                    }
                }
                catch (const std::exception&)
                {}
            }
            FEATHER_TK_ASSERT(0 == r);
        }
    }
}
