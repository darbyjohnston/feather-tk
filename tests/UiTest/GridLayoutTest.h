// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class GridLayoutTest : public test::ITest
        {
        protected:
            GridLayoutTest(const std::shared_ptr<Context>&);

        public:
            virtual ~GridLayoutTest();

            static std::shared_ptr<GridLayoutTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

