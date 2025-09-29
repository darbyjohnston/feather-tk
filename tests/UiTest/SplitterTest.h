// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/Ui/App.h>
#include <ftk/Ui/Window.h>

#include <TestLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class SplitterTest : public test::ITest
        {
        protected:
            SplitterTest(const std::shared_ptr<Context>&);

        public:
            virtual ~SplitterTest();

            static std::shared_ptr<SplitterTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _test(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<App>&,
                const std::shared_ptr<Window>&,
                Orientation);
        };
    }
}

