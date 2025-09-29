// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class FloatEditTest : public test::ITest
        {
        protected:
            FloatEditTest(const std::shared_ptr<Context>&);

        public:
            virtual ~FloatEditTest();

            static std::shared_ptr<FloatEditTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

