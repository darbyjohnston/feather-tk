// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class GroupBoxTest : public test::ITest
        {
        protected:
            GroupBoxTest(const std::shared_ptr<Context>&);

        public:
            virtual ~GroupBoxTest();

            static std::shared_ptr<GroupBoxTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

