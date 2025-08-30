// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class PieChartTest : public test::ITest
        {
        protected:
            PieChartTest(const std::shared_ptr<Context>&);

        public:
            virtual ~PieChartTest();

            static std::shared_ptr<PieChartTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

