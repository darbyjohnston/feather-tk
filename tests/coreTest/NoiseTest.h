// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace core_test
    {
        class NoiseTest : public test::ITest
        {
        protected:
            NoiseTest(const std::shared_ptr<Context>&);

        public:
            virtual ~NoiseTest();

            static std::shared_ptr<NoiseTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

