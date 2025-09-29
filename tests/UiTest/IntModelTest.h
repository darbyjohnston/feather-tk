// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class IntModelTest : public test::ITest
        {
        protected:
            IntModelTest(const std::shared_ptr<Context>&);

        public:
            virtual ~IntModelTest();

            static std::shared_ptr<IntModelTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

