// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class LayoutUtilTest : public test::ITest
        {
        protected:
            LayoutUtilTest(const std::shared_ptr<Context>&);

        public:
            virtual ~LayoutUtilTest();

            static std::shared_ptr<LayoutUtilTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

