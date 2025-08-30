// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace core_test
    {
        class TimeTest : public test::ITest
        {
        protected:
            TimeTest(const std::shared_ptr<Context>&);

        public:
            virtual ~TimeTest();

            static std::shared_ptr<TimeTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        
        private:
            void _sleep();
            void _rational();
        };
    }
}

