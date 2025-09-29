// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace core_test
    {
        class CmdLineTest : public test::ITest
        {
        protected:
            CmdLineTest(const std::shared_ptr<Context>&);

        public:
            virtual ~CmdLineTest();

            static std::shared_ptr<CmdLineTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

