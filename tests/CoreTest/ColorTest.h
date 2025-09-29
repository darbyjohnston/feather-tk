// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace core_test
    {
        class ColorTest : public test::ITest
        {
        protected:
            ColorTest(const std::shared_ptr<Context>&);

        public:
            virtual ~ColorTest();

            static std::shared_ptr<ColorTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _members();
            void _operators();
            void _functions();
            void _serialize();
        };
    }
}

