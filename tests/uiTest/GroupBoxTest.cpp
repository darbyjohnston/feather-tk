// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/GroupBoxTest.h>

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/GroupBox.h>
#include <feather-tk/ui/RowLayout.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        GroupBoxTest::GroupBoxTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::GroupBoxTest")
        {}

        GroupBoxTest::~GroupBoxTest()
        {}

        std::shared_ptr<GroupBoxTest> GroupBoxTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<GroupBoxTest>(new GroupBoxTest(context));
        }
                
        void GroupBoxTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("GroupBoxTest");
                auto app = App::create(
                    context,
                    argv,
                    "GroupBoxTest",
                    "Group box test.");
                auto window = Window::create(context, "GroupBoxTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto widget = GroupBox::create(context, "Test", layout);
                widget->setText("Group");
                widget->setText("Group");
                FEATHER_TK_ASSERT("Group" == widget->getText());
                widget->setFontRole(FontRole::Mono);
                widget->setFontRole(FontRole::Mono);
                FEATHER_TK_ASSERT(FontRole::Mono == widget->getFontRole());
                widget->setFontRole(FontRole::Label);
                app->tick();
            }
        }
    }
}

