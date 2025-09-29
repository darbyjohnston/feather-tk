// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/Ui/App.h>
#include <ftk/Ui/RowLayout.h>
#include <ftk/Ui/Window.h>

#include <TestLib/ITest.h>

namespace ftk
{
    namespace ui_test
    {
        class ScrollBarTest : public test::ITest
        {
        protected:
            ScrollBarTest(const std::shared_ptr<Context>&);

        public:
            virtual ~ScrollBarTest();

            static std::shared_ptr<ScrollBarTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _test(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<App>&,
                const std::shared_ptr<Window>&,
                const std::shared_ptr<VerticalLayout>&,
                Orientation);
        };
    }
}

