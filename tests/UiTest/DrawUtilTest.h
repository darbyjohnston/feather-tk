// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class DrawUtilTest : public test::ITest
        {
        protected:
            DrawUtilTest(const std::shared_ptr<Context>&);

        public:
            virtual ~DrawUtilTest();

            static std::shared_ptr<DrawUtilTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

