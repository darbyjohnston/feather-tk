// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace gl_test
    {
        class OffscreenBufferTest : public test::ITest
        {
        protected:
            OffscreenBufferTest(const std::shared_ptr<Context>&);

        public:
            virtual ~OffscreenBufferTest();

            static std::shared_ptr<OffscreenBufferTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _enums();
            void _members();
            void _functions();
            void _operators();
        };
    }
}

