// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class FileBrowserTest : public test::ITest
        {
        protected:
            FileBrowserTest(const std::shared_ptr<Context>&);

        public:
            virtual ~FileBrowserTest();

            static std::shared_ptr<FileBrowserTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _enums();
            void _shortcuts();
            void _view();
            void _widget();
            void _dialog();
        };
    }
}

