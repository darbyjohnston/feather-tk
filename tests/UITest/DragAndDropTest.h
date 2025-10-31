// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class DragAndDropTest : public test::ITest
        {
        protected:
            DragAndDropTest(const std::shared_ptr<Context>&);

        public:
            virtual ~DragAndDropTest();

            static std::shared_ptr<DragAndDropTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

