// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <UiTest/ScrollAreaTest.h>

#include <ftk/Ui/ScrollArea.h>

#include <ftk/Core/Assert.h>
#include <ftk/Core/Format.h>

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

