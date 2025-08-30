// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace core_test
    {
        class ImageTest : public test::ITest
        {
        protected:
            ImageTest(const std::shared_ptr<Context>&);

        public:
            virtual ~ImageTest();

            static std::shared_ptr<ImageTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
            
        private:
            void _enums();
            void _info();
            void _members();
            void _functions();
        };
    }
}

