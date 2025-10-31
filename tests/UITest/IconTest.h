// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class IconTest : public test::ITest
        {
        protected:
            IconTest(const std::shared_ptr<Context>&);

        public:
            virtual ~IconTest();

            static std::shared_ptr<IconTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

