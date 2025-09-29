// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace core_test
    {
        class MemoryTest : public test::ITest
        {
        protected:
            MemoryTest(const std::shared_ptr<Context>&);

        public:
            virtual ~MemoryTest();

            static std::shared_ptr<MemoryTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _enums();
            void _endian();
            void _bits();
        };
    }
}

