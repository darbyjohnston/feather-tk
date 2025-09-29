// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/Ui/App.h>
#include <ftk/Ui/ButtonGroup.h>
#include <ftk/Ui/Window.h>

#include <testLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class ListWidgetTest : public test::ITest
        {
        protected:
            ListWidgetTest(const std::shared_ptr<Context>&);

        public:
            virtual ~ListWidgetTest();

            static std::shared_ptr<ListWidgetTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _test(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<App>&,
                const std::shared_ptr<Window>&,
                ButtonGroupType);
        };
    }
}

