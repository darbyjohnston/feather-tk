// SPDX-License-Identifier: BSD-3-Clause
// Cspyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace core_test
    {
        class FileTest : public test::ITest
        {
        protected:
            FileTest(const std::shared_ptr<Context>&);

        public:
            virtual ~FileTest();

            static std::shared_ptr<FileTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _util();
            void _split();
            void _drives();
            void _userPaths();
        };
    }
}

