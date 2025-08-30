// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace core_test
    {
        class AppTest : public test::ITest
        {
        protected:
            AppTest(const std::shared_ptr<Context>&);

        public:
            virtual ~AppTest();

            static std::shared_ptr<AppTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

