// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class MessageDialogTest : public test::ITest
        {
        protected:
            MessageDialogTest(const std::shared_ptr<Context>&);

        public:
            virtual ~MessageDialogTest();

            static std::shared_ptr<MessageDialogTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

