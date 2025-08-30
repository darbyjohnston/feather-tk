// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace core_test
    {
        class RangeTest : public test::ITest
        {
        protected:
            RangeTest(const std::shared_ptr<Context>&);

        public:
            virtual ~RangeTest();

            static std::shared_ptr<RangeTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _members();
            void _functions();
            void _serialize();
        };
    }
}

