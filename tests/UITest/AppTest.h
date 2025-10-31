// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class AppTest : public test::ITest
        {
        protected:
            AppTest(const std::shared_ptr<Context>&);

        public:
            virtual ~AppTest();

            static std::shared_ptr<AppTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

