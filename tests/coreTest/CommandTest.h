// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace feather_tk
{
    namespace core_test
    {
        class CommandTest : public test::ITest
        {
        protected:
            CommandTest(const std::shared_ptr<Context>&);

        public:
            virtual ~CommandTest();

            static std::shared_ptr<CommandTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

