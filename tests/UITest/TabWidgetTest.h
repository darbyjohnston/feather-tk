// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class TabWidgetTest : public test::ITest
        {
        protected:
            TabWidgetTest(const std::shared_ptr<Context>&);

        public:
            virtual ~TabWidgetTest();

            static std::shared_ptr<TabWidgetTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _bar();
            void _widget();
        };
    }
}

