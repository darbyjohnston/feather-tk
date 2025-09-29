// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace core_test
    {
        class RenderOptionsTest : public test::ITest
        {
        protected:
            RenderOptionsTest(const std::shared_ptr<Context>&);

        public:
            virtual ~RenderOptionsTest();

            static std::shared_ptr<RenderOptionsTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _enums();
            void _operators();
        };
    }
}

