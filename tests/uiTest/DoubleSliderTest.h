// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class DoubleSliderTest : public test::ITest
        {
        protected:
            DoubleSliderTest(const std::shared_ptr<Context>&);

        public:
            virtual ~DoubleSliderTest();

            static std::shared_ptr<DoubleSliderTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

