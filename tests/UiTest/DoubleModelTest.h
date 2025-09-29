// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class DoubleModelTest : public test::ITest
        {
        protected:
            DoubleModelTest(const std::shared_ptr<Context>&);

        public:
            virtual ~DoubleModelTest();

            static std::shared_ptr<DoubleModelTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

