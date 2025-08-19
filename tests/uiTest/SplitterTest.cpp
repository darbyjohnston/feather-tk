// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/SplitterTest.h>

#include <feather-tk/ui/Label.h>
#include <feather-tk/ui/Splitter.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        SplitterTest::SplitterTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::SplitterTest")
        {}

        SplitterTest::~SplitterTest()
        {}

        std::shared_ptr<SplitterTest> SplitterTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<SplitterTest>(new SplitterTest(context));
        }
                
        void SplitterTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("SplitterTest");
                auto app = App::create(
                    context,
                    argv,
                    "SplitterTest",
                    "Splitter test.");
                auto window = Window::create(context, "SplitterTest");
                app->addWindow(window);
                window->show();
                app->tick();
                _test(context, app, window, Orientation::Horizontal);
                _test(context, app, window, Orientation::Vertical);
            }
        }

        void SplitterTest::_test(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<Window>& window,
            Orientation orientation)
        {
            auto splitter = Splitter::create(context, orientation, window);
            float split = .9F;
            splitter->setSplit(split);
            splitter->setSplit(split);
            FEATHER_TK_ASSERT(split == splitter->getSplit());
            app->tick();

            auto label0 = Label::create(context, "Label 0", splitter);
            auto label1 = Label::create(context, "Label 1", splitter);
            app->tick();
            splitter->setSplit(.1F);
            app->tick();
            splitter->setSplit(.5F);
            app->tick();

            splitter->setParent(nullptr);
        }
    }
}

