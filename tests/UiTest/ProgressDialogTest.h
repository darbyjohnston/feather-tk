// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class ProgressDialogTest : public test::ITest
        {
        protected:
            ProgressDialogTest(const std::shared_ptr<Context>&);

        public:
            virtual ~ProgressDialogTest();

            static std::shared_ptr<ProgressDialogTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

