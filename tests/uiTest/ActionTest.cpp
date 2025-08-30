// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/ActionTest.h>

#include <ftk/ui/Action.h>

#include <ftk/core/Assert.h>
#include <ftk/core/Format.h>

namespace ftk
{
    namespace ui_test
    {
        ActionTest::ActionTest(const std::shared_ptr<Context>& context) :
            ITest(context, "ftk::ui_test::ActionTest")
        {}

        ActionTest::~ActionTest()
        {}

        std::shared_ptr<ActionTest> ActionTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ActionTest>(new ActionTest(context));
        }
                
        void ActionTest::run()
        {
            {
                auto a = Action::create(
                    "Test",
                    [] {});
                FTK_ASSERT("Test" == a->getText());
            }
            {
                auto a = Action::create(
                    "Test",
                    "Icon",
                    [] {});
                FTK_ASSERT("Test" == a->getText());
                FTK_ASSERT("Icon" == a->getIcon());
            }
            {
                auto a = Action::create(
                    "Test",
                    Key::T,
                    static_cast<int>(KeyModifier::Control),
                    [] {});
                FTK_ASSERT("Test" == a->getText());
                FTK_ASSERT(Key::T == a->getShortcut());
                FTK_ASSERT(static_cast<int>(KeyModifier::Control) == a->getShortcutModifiers());
            }
            {
                auto a = Action::create(
                    "Test",
                    "Icon",
                    Key::T,
                    static_cast<int>(KeyModifier::Control),
                    [] {});
                FTK_ASSERT("Test" == a->getText());
                FTK_ASSERT("Icon" == a->getIcon());
                FTK_ASSERT(Key::T == a->getShortcut());
                FTK_ASSERT(static_cast<int>(KeyModifier::Control) == a->getShortcutModifiers());
            }
            {
                auto a = Action::create(
                    "Test",
                    [](bool) {});
                FTK_ASSERT("Test" == a->getText());
            }
            {
                auto a = Action::create(
                    "Test",
                    "Icon",
                    [](bool) {});
                FTK_ASSERT("Test" == a->getText());
                FTK_ASSERT("Icon" == a->getIcon());
            }
            {
                auto a = Action::create(
                    "Test",
                    Key::T,
                    static_cast<int>(KeyModifier::Control),
                    [](bool) {});
                FTK_ASSERT("Test" == a->getText());
                FTK_ASSERT(Key::T == a->getShortcut());
                FTK_ASSERT(static_cast<int>(KeyModifier::Control) == a->getShortcutModifiers());
            }
            {
                auto a = Action::create(
                    "Test",
                    "Icon",
                    Key::T,
                    static_cast<int>(KeyModifier::Control),
                    [](bool) {});
                FTK_ASSERT("Test" == a->getText());
                FTK_ASSERT("Icon" == a->getIcon());
                FTK_ASSERT(Key::T == a->getShortcut());
                FTK_ASSERT(static_cast<int>(KeyModifier::Control) == a->getShortcutModifiers());
            }
        }
    }
}

