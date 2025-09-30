// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <UITest/SearchBoxTest.h>

#include <ftk/UI/App.h>
#include <ftk/UI/SearchBox.h>
#include <ftk/UI/RowLayout.h>
#include <ftk/UI/Window.h>

#include <ftk/Core/Assert.h>
#include <ftk/Core/Format.h>

namespace ftk
{
    namespace ui_test
    {
        SearchBoxTest::SearchBoxTest(const std::shared_ptr<Context>& context) :
            ITest(context, "ftk::ui_test::SearchBoxTest")
        {}

        SearchBoxTest::~SearchBoxTest()
        {}

        std::shared_ptr<SearchBoxTest> SearchBoxTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<SearchBoxTest>(new SearchBoxTest(context));
        }
                
        void SearchBoxTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("SearchBoxTest");
                auto app = App::create(
                    context,
                    argv,
                    "SearchBoxTest",
                    "Search box test.");
                auto window = Window::create(context, "SearchBoxTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto widget = SearchBox::create(context, layout);
                std::string text;
                widget->setCallback(
                    [&text](const std::string& value)
                    {
                        text = value;
                    });
                widget->setText("Search");
                widget->setText("Search");
                FTK_ASSERT("Search" == widget->getText());
            }
        }
    }
}

