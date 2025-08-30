// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class MDIWidgetTest : public test::ITest
        {
        protected:
            MDIWidgetTest(const std::shared_ptr<Context>&);

        public:
            virtual ~MDIWidgetTest();

            static std::shared_ptr<MDIWidgetTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _enums();
            void _widget();
        };
    }
}

