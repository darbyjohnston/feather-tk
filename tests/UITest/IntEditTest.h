// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class IntEditTest : public test::ITest
        {
        protected:
            IntEditTest(const std::shared_ptr<Context>&);

        public:
            virtual ~IntEditTest();

            static std::shared_ptr<IntEditTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

