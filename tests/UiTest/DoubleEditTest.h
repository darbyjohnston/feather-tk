// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class DoubleEditTest : public test::ITest
        {
        protected:
            DoubleEditTest(const std::shared_ptr<Context>&);

        public:
            virtual ~DoubleEditTest();

            static std::shared_ptr<DoubleEditTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

