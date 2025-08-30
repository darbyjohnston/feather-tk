// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/WidgetOptionsTest.h>

#include <feather-tk/ui/WidgetOptions.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace ftk
{
    namespace ui_test
    {
        WidgetOptionsTest::WidgetOptionsTest(const std::shared_ptr<Context>& context) :
            ITest(context, "ftk::ui_test::WidgetOptionsTest")
        {}

        WidgetOptionsTest::~WidgetOptionsTest()
        {}

        std::shared_ptr<WidgetOptionsTest> WidgetOptionsTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<WidgetOptionsTest>(new WidgetOptionsTest(context));
        }
                
        void WidgetOptionsTest::run()
        {
            _enums();
        }
        
        void WidgetOptionsTest::_enums()
        {
            FTK_TEST_ENUM(Orientation);
            FTK_TEST_ENUM(Stretch);
            FTK_TEST_ENUM(HAlign);
            FTK_TEST_ENUM(VAlign);
        }
    }
}

