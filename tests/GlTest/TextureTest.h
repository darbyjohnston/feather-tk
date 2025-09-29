// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace gl_test
    {
        class TextureTest : public test::ITest
        {
        protected:
            TextureTest(const std::shared_ptr<Context>&);

        public:
            virtual ~TextureTest();

            static std::shared_ptr<TextureTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _members();
            void _functions();
            void _operators();
        };
    }
}

