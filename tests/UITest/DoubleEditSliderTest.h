// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class DoubleEditSliderTest : public test::ITest
        {
        protected:
            DoubleEditSliderTest(const std::shared_ptr<Context>&);

        public:
            virtual ~DoubleEditSliderTest();

            static std::shared_ptr<DoubleEditSliderTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

