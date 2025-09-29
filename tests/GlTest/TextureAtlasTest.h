// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace gl_test
    {
        class TextureAtlasTest : public test::ITest
        {
        protected:
            TextureAtlasTest(const std::shared_ptr<Context>&);

        public:
            virtual ~TextureAtlasTest();

            static std::shared_ptr<TextureAtlasTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

