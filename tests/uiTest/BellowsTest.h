// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class BellowsTest : public test::ITest
        {
        protected:
            BellowsTest(const std::shared_ptr<Context>&);

        public:
            virtual ~BellowsTest();

            static std::shared_ptr<BellowsTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

