// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class RecentFilesModelTest : public test::ITest
        {
        protected:
            RecentFilesModelTest(const std::shared_ptr<Context>&);

        public:
            virtual ~RecentFilesModelTest();

            static std::shared_ptr<RecentFilesModelTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

