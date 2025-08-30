// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/ScrollAreaTest.h>

#include <feather-tk/ui/ScrollArea.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace ftk
{
    namespace ui_test
    {
        ScrollAreaTest::ScrollAreaTest(const std::shared_ptr<Context>& context) :
            ITest(context, "ftk::ui_test::ScrollAreaTest")
        {}

        ScrollAreaTest::~ScrollAreaTest()
        {}

        std::shared_ptr<ScrollAreaTest> ScrollAreaTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ScrollAreaTest>(new ScrollAreaTest(context));
        }
                
        void ScrollAreaTest::run()
        {
            _enums();
        }
        
        void ScrollAreaTest::_enums()
        {
            FTK_TEST_ENUM(ScrollType);
        }
    }
}

