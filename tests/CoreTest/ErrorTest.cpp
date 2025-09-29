// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <CoreTest/ErrorTest.h>

#include <ftk/Core/Assert.h>
#include <ftk/Core/Error.h>

namespace ftk
{
    namespace core_test
    {
        ErrorTest::ErrorTest(const std::shared_ptr<Context>& context) :
            ITest(context, "ftk::core_test::ErrorTest")
        {}

        ErrorTest::~ErrorTest()
        {}

        std::shared_ptr<ErrorTest> ErrorTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ErrorTest>(new ErrorTest(context));
        }
        
        void ErrorTest::run()
        {
            try
            {
                throw ParseError();
            }
            catch (const std::exception&)
            {}
        }
    }
}

