// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace core_test
    {
        class RandomTest : public test::ITest
        {
        protected:
            RandomTest(const std::shared_ptr<Context>&);

        public:
            virtual ~RandomTest();

            static std::shared_ptr<RandomTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

