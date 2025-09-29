// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace ftk
{
    namespace core_test
    {
        class ObservableTest : public test::ITest
        {
        protected:
            ObservableTest(const std::shared_ptr<Context>&);

        public:
            virtual ~ObservableTest();

            static std::shared_ptr<ObservableTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _value();
            void _list();
            void _map();
        };
    }
}

