// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <GlTest/WindowTest.h>

#include <ftk/Gl/Window.h>

#include <ftk/Core/Assert.h>
#include <ftk/Core/Format.h>

using namespace ftk::gl;

namespace ftk
{
    namespace gl_test
    {
        WindowTest::WindowTest(const std::shared_ptr<Context>& context) :
            ITest(context, "ftk::gl_test::WindowTest")
        {}

        WindowTest::~WindowTest()
        {}

        std::shared_ptr<WindowTest> WindowTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<WindowTest>(new WindowTest(context));
        }
        
        void WindowTest::run()
        {
            if (auto context = _context.lock())
            {
                Size2I size(1024, 1024);
                auto window = Window::create(context, "WindowTest", size);
                FTK_ASSERT(window->getID());
                _print(Format("Screen: {0}").arg(window->getScreen()));
                _print(Format("Full screen: {0}").arg(window->isFullScreen()));
                _print(Format("Float on top: {0}").arg(window->isFloatOnTop()));

                size = Size2I(512, 512);
                window->setSize(size);
                window->hide();
                window->show();
                window->setFullScreen(true);
                window->setFullScreen(true);
                window->setFullScreen(false);
                window->setFloatOnTop(true);
                window->setFloatOnTop(true);
                window->setFloatOnTop(false);
                window->makeCurrent();
                window->swap();
                window->clearCurrent();
            }
        }
    }
}

