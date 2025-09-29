// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <TestLib/ITest.h>

namespace ftk
{
    namespace core_test
    {
        class StringTest : public test::ITest
        {
        protected:
            StringTest(const std::shared_ptr<Context>&);

        public:
            virtual ~StringTest();

            static std::shared_ptr<StringTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _split();
            void _format();
            void _compare();
            void _convert();
            void _filler();
        };
    }
}

