// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

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

