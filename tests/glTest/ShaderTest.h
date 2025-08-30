// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace gl_test
    {
        class ShaderTest : public test::ITest
        {
        protected:
            ShaderTest(const std::shared_ptr<Context>&);

        public:
            virtual ~ShaderTest();

            static std::shared_ptr<ShaderTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

