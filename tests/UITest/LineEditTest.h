// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class LineEditTest : public test::ITest
        {
        protected:
            LineEditTest(const std::shared_ptr<Context>&);

        public:
            virtual ~LineEditTest();

            static std::shared_ptr<LineEditTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

