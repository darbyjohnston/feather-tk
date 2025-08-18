// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/ButtonGroupTest.h>

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/ButtonGroup.h>
#include <feather-tk/ui/RowLayout.h>
#include <feather-tk/ui/PushButton.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        ButtonGroupTest::ButtonGroupTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::ButtonGroupTest")
        {}

        ButtonGroupTest::~ButtonGroupTest()
        {}

        std::shared_ptr<ButtonGroupTest> ButtonGroupTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ButtonGroupTest>(new ButtonGroupTest(context));
        }
                
        void ButtonGroupTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("ButtonGroupTest");
                auto app = App::create(
                    context,
                    argv,
                    "ButtonGroupTest",
                    "Button group test.");
                auto window = Window::create(context, app, "ButtonGroupTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto button0 = PushButton::create(context, "Button 0", layout);
                auto button1 = PushButton::create(context, "Button 0", layout);
                auto button2 = PushButton::create(context, "Button 0", layout);
                auto group = ButtonGroup::create(context, ButtonGroupType::Click);
                group->addButton(button0);
                FEATHER_TK_ASSERT(!group->getButtons().empty());
                group->clearButtons();
                FEATHER_TK_ASSERT(group->getButtons().empty());
                group->addButton(button0);
                group->addButton(button1);
                group->addButton(button2);
                int clicked = -1;
                group->setClickedCallback(
                    [&clicked](int value)
                    {
                        clicked = value;
                    });

                group = ButtonGroup::create(context, ButtonGroupType::Check);
                group->addButton(button0);
                group->addButton(button1);
                group->addButton(button2);
                clicked = -1;
                bool checked = false;
                group->setCheckedCallback(
                    [&clicked, &checked](int index, bool value)
                    {
                        clicked = index;
                        checked = value;
                    });

                group = ButtonGroup::create(context, ButtonGroupType::Radio);
                group->addButton(button0);
                group->addButton(button1);
                group->addButton(button2);
                clicked = -1;
                checked = false;
                group->setCheckedCallback(
                    [&clicked, &checked](int index, bool value)
                    {
                        clicked = index;
                        checked = value;
                    });

                group = ButtonGroup::create(context, ButtonGroupType::Toggle);
                group->addButton(button0);
                group->addButton(button1);
                group->addButton(button2);
                clicked = -1;
                checked = false;
                group->setCheckedCallback(
                    [&clicked, &checked](int index, bool value)
                    {
                        clicked = index;
                        checked = value;
                    });
            }
        }
    }
}

