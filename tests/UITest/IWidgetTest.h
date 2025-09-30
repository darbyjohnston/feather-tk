// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class IWidgetTest : public test::ITest
        {
        protected:
            IWidgetTest(const std::shared_ptr<Context>&);

        public:
            virtual ~IWidgetTest();

            static std::shared_ptr<IWidgetTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

