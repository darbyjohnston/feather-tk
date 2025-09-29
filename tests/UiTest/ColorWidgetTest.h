// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class ColorWidgetTest : public test::ITest
        {
        protected:
            ColorWidgetTest(const std::shared_ptr<Context>&);

        public:
            virtual ~ColorWidgetTest();

            static std::shared_ptr<ColorWidgetTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

