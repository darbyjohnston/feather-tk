// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/ButtonTest.h>

#include <feather-tk/ui/CheckBox.h>
#include <feather-tk/ui/PushButton.h>
#include <feather-tk/ui/ToolButton.h>
#include <feather-tk/ui/Tooltip.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>
#include <feather-tk/core/Time.h>

namespace feather_tk
{
    namespace ui_test
    {
        ButtonTest::ButtonTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::ButtonTest")
        {}

        ButtonTest::~ButtonTest()
        {}

        std::shared_ptr<ButtonTest> ButtonTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ButtonTest>(new ButtonTest(context));
        }

        void ButtonTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("ButtonTest");
                auto app = App::create(
                    context,
                    argv,
                    "ButtonTest",
                    "Button test.");
                auto window = Window::create(context, "ButtonTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                PushButton::create(context, "Push", layout);

                std::shared_ptr<IButton> button = PushButton::create(context, "Push", layout);
                button->setObjectName("PushButton");
                _print(button->getObjectName());
                _print(button->getObjectPath());
                _test(app, window, layout, button);
                button->setParent(nullptr);
                button.reset();

                button = ToolButton::create(context, "Tool", layout);
                _test(app, window, layout, button);
                button->setParent(nullptr);
                button.reset();

                button = CheckBox::create(context, "CheckBox", layout);
                _test(app, window, layout, button);
                std::string tooltip = "This is a tooltip";
                button->setTooltip(tooltip);
                FEATHER_TK_ASSERT(tooltip == button->getTooltip());
                button->setParent(nullptr);
                button.reset();
            }
        }

        void ButtonTest::_test(
            const std::shared_ptr<App>& app,
            const std::shared_ptr<Window>& window,
            const std::shared_ptr<VerticalLayout>& layout,
            const std::shared_ptr<IButton>& button)
        {
            FEATHER_TK_ASSERT(button->getParent().lock());
            FEATHER_TK_ASSERT(button->getParentT<Window>());
            FEATHER_TK_ASSERT(button->getWindow());

            std::string text = "Playback";
            button->setText(text);
            button->setText(text);
            FEATHER_TK_ASSERT(text == button->getText());

            FontRole fontRole = FontRole::Mono;
            button->setFontRole(fontRole);
            button->setFontRole(fontRole);
            FEATHER_TK_ASSERT(fontRole == button->getFontRole());

            button->setCheckable(true);
            button->setCheckable(true);
            FEATHER_TK_ASSERT(button->isCheckable());
            button->setChecked(true);
            button->setChecked(true);
            FEATHER_TK_ASSERT(button->isChecked());
            button->setCheckable(false);
            FEATHER_TK_ASSERT(!button->isChecked());
            button->setCheckable(true);

            std::string icon = "PlaybackForward";
            button->setIcon(icon);
            button->setIcon(icon);
            FEATHER_TK_ASSERT(icon == button->getIcon());
            icon = "PlaybackStop";
            button->setCheckedIcon(icon);
            button->setCheckedIcon(icon);
            FEATHER_TK_ASSERT(icon == button->getCheckedIcon());

            ColorRole colorRole = ColorRole::Red;
            button->setBackgroundRole(colorRole);
            button->setBackgroundRole(colorRole);
            FEATHER_TK_ASSERT(colorRole == button->getBackgroundRole());
            colorRole = ColorRole::Green;
            button->setButtonRole(colorRole);
            button->setButtonRole(colorRole);
            FEATHER_TK_ASSERT(colorRole == button->getButtonRole());
            colorRole = ColorRole::Blue;
            button->setCheckedRole(colorRole);
            button->setCheckedRole(colorRole);
            FEATHER_TK_ASSERT(colorRole == button->getCheckedRole());

            button->hide();
            button->hide();
            app->tick();
            button->show();
            app->tick();

            button->setEnabled(false);
            button->setEnabled(false);
            app->tick();
            button->setEnabled(true);
            app->tick();

            bool hovered = false;
            button->setHoveredCallback([&hovered](bool value) { hovered = value; });
            bool pressed = false;
            button->setPressedCallback([&pressed] { pressed = true; });
            int clicks = 0;
            button->setRepeatClick(true);
            FEATHER_TK_ASSERT(button->hasRepeatClick());
            button->setClickedCallback([&clicks] { ++clicks; });
            bool checked = false;
            button->setCheckedCallback([&checked](bool value) { checked = value; });

            app->setDisplayScale(2.F);
            app->tick();
            app->setDisplayScale(1.F);
            app->tick();
        }
    }
}

