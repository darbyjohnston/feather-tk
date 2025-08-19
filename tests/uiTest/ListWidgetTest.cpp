// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/ListWidgetTest.h>

#include <feather-tk/ui/ListWidget.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        ListWidgetTest::ListWidgetTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::ListWidgetTest")
        {}

        ListWidgetTest::~ListWidgetTest()
        {}

        std::shared_ptr<ListWidgetTest> ListWidgetTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ListWidgetTest>(new ListWidgetTest(context));
        }
                
        void ListWidgetTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("ListWidgetTest");
                auto app = App::create(
                    context,
                    argv,
                    "ListWidgetTest",
                    "List widget test.");
                auto window = Window::create(context, "ListWidgetTest");
                app->addWindow(window);
                window->show();
                app->tick();
                _test(context, app, window, ButtonGroupType::Click);
                _test(context, app, window, ButtonGroupType::Check);
                _test(context, app, window, ButtonGroupType::Radio);
                _test(context, app, window, ButtonGroupType::Toggle);
            }
        }

        void ListWidgetTest::_test(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<Window>& window,
            ButtonGroupType type)
        {
            auto widget = ListWidget::create(context, type, window);
            std::vector<ListItem> items =
            {
                ListItem("Item 0"),
                ListItem("Item 1"),
                ListItem("Item 2"),
                ListItem("Item 3")
            };
            widget->setItems(items);
            widget->setItems(items);
            FEATHER_TK_ASSERT(items == widget->getItems());
            app->tick();
            items.push_back(ListItem("Item 4"));
            widget->setItems(items);
            app->tick();
            widget->setSearch("4");
            widget->setSearch("4");
            FEATHER_TK_ASSERT("4" == widget->getSearch());
            app->tick();
            widget->clearSearch();
            FEATHER_TK_ASSERT(widget->getSearch().empty());
            app->tick();
        }
    }
}

