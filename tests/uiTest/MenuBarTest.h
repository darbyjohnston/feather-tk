// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace feather_tk
{
    namespace ui_test
    {
        class MenuBarTest : public test::ITest
        {
        protected:
            MenuBarTest(const std::shared_ptr<Context>&);

        public:
            virtual ~MenuBarTest();

            static std::shared_ptr<MenuBarTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

