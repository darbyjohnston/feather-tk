// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class LabelTest : public test::ITest
        {
        protected:
            LabelTest(const std::shared_ptr<Context>&);

        public:
            virtual ~LabelTest();

            static std::shared_ptr<LabelTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

