// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class WidgetOptionsTest : public test::ITest
        {
        protected:
            WidgetOptionsTest(const std::shared_ptr<Context>&);

        public:
            virtual ~WidgetOptionsTest();

            static std::shared_ptr<WidgetOptionsTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _enums();
        };
    }
}

