// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace gl_test
    {
        class UtilTest : public test::ITest
        {
        protected:
            UtilTest(const std::shared_ptr<Context>&);

        public:
            virtual ~UtilTest();

            static std::shared_ptr<UtilTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

