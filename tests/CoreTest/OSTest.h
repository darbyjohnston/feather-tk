// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace core_test
    {
        class OSTest : public test::ITest
        {
        protected:
            OSTest(const std::shared_ptr<Context>&);

        public:
            virtual ~OSTest();

            static std::shared_ptr<OSTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _env();
        };
    }
}

