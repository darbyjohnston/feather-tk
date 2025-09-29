// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <UiTest/GroupBoxTest.h>

#include <ftk/Ui/App.h>
#include <ftk/Ui/GroupBox.h>
#include <ftk/Ui/RowLayout.h>
#include <ftk/Ui/Window.h>

#include <ftk/Core/Assert.h>
#include <ftk/Core/Format.h>

namespace ftk
{
    namespace ui_test
    {
        GroupBoxTest::GroupBoxTest(const std::shared_ptr<Context>& context) :
            ITest(context, "ftk::ui_test::GroupBoxTest")
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
                FTK_ASSERT("Group" == widget->getText());
                widget->setFontRole(FontRole::Mono);
                widget->setFontRole(FontRole::Mono);
                FTK_ASSERT(FontRole::Mono == widget->getFontRole());
                widget->setFontRole(FontRole::Label);
                app->tick();
            }
        }
    }
}

