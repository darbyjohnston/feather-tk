// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

#include <feather-tk/core/BoxPack.h>

namespace ftk
{
    namespace core_test
    {
        class BoxPackTest : public test::ITest
        {
        protected:
            BoxPackTest(const std::shared_ptr<Context>&);

        public:
            virtual ~BoxPackTest();

            static std::shared_ptr<BoxPackTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _printPack(const std::shared_ptr<BoxPack>&);
            void _printNode(
                const std::shared_ptr<BoxPackNode>&,
                int indent = 0,
                char pad = ' ');
        };
    }
}

