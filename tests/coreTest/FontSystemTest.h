// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace feather_tk
{
    namespace core_test
    {
        class FontSystemTest : public test::ITest
        {
        protected:
            FontSystemTest(const std::shared_ptr<Context>&);

        public:
            virtual ~FontSystemTest();

            static std::shared_ptr<FontSystemTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

