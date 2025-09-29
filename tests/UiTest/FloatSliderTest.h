// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class FloatSliderTest : public test::ITest
        {
        protected:
            FloatSliderTest(const std::shared_ptr<Context>&);

        public:
            virtual ~FloatSliderTest();

            static std::shared_ptr<FloatSliderTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

