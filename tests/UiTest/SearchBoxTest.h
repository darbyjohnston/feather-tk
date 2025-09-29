// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class SearchBoxTest : public test::ITest
        {
        protected:
            SearchBoxTest(const std::shared_ptr<Context>&);

        public:
            virtual ~SearchBoxTest();

            static std::shared_ptr<SearchBoxTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

