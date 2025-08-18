// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <glTest/UtilTest.h>

#include <feather-tk/gl/Util.h>

#include <feather-tk/core/Assert.h>

using namespace feather_tk::gl;

namespace feather_tk
{
    namespace gl_test
    {
        UtilTest::UtilTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::gl_test::UtilTest")
        {}

        UtilTest::~UtilTest()
        {}

        std::shared_ptr<UtilTest> UtilTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<UtilTest>(new UtilTest(context));
        }
                
        void UtilTest::run()
        {
            FEATHER_TK_ASSERT(4 == getMajorVersion("4.1.0 Driver 571.59"));
            FEATHER_TK_ASSERT(3 == getMajorVersion("OpenGL ES 3.2 Mesa 25.0.7"));
        }
    }
}

