// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

#include <ftk/Ui/App.h>
#include <ftk/Ui/IButton.h>
#include <ftk/Ui/RowLayout.h>

namespace ftk
{
    namespace ui_test
    {
        class ButtonTest : public test::ITest
        {
        protected:
            ButtonTest(const std::shared_ptr<Context>&);

        public:
            virtual ~ButtonTest();

            static std::shared_ptr<ButtonTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _test(
                const std::shared_ptr<App>&,
                const std::shared_ptr<Window>&,
                const std::shared_ptr<VerticalLayout>&,
                const std::shared_ptr<IButton>&);
        };
    }
}

