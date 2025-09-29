// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

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

