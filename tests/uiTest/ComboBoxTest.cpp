// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/ComboBoxTest.h>

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/ComboBox.h>
#include <feather-tk/ui/RowLayout.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        ComboBoxTest::ComboBoxTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::ComboBoxTest")
        {}

        ComboBoxTest::~ComboBoxTest()
        {}

        std::shared_ptr<ComboBoxTest> ComboBoxTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ComboBoxTest>(new ComboBoxTest(context));
        }
                
        void ComboBoxTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("ComboBoxTest");
                auto app = App::create(
                    context,
                    argv,
                    "ComboBoxTest",
                    "Combo box test.");
                auto window = Window::create(context, app, "ComboBoxTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                std::vector<ComboBoxItem> items =
                {
                    ComboBoxItem("Stop", "PlaybackStop"),
                    ComboBoxItem("Forward", "PlaybackForward"),
                    ComboBoxItem("Reverse", "PlaybackReverse")
                };
                auto widget = ComboBox::create(context, items, layout);
                FEATHER_TK_ASSERT(items[0] != ComboBoxItem());
                widget->setItems(items);
                widget->setItems(items);
                FEATHER_TK_ASSERT(items == widget->getItems());
                FEATHER_TK_ASSERT(0 == widget->getCurrentIndex());
                widget->setCurrentIndex(1);
                widget->setCurrentIndex(1);
                FEATHER_TK_ASSERT(1 == widget->getCurrentIndex());
                int index = -1;
                widget->setIndexCallback(
                    [&index](int value)
                    {
                        index = value;
                    });
                ComboBoxItem item;
                widget->setItemCallback(
                    [&item](const ComboBoxItem& value)
                    {
                        item = value;
                    });
                widget->setFontRole(FontRole::Mono);
                widget->setFontRole(FontRole::Mono);
                FEATHER_TK_ASSERT(FontRole::Mono == widget->getFontRole());
                widget->setFontRole(FontRole::Label);

                app->setDisplayScale(2.F);
                app->tick();
                app->setDisplayScale(1.F);
                app->tick();
            }
        }
    }
}

