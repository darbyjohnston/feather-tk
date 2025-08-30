// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/IntModelTest.h>

#include <ftk/ui/IntModel.h>

#include <ftk/core/Assert.h>
#include <ftk/core/Format.h>

namespace ftk
{
    namespace ui_test
    {
        IntModelTest::IntModelTest(const std::shared_ptr<Context>& context) :
            ITest(context, "ftk::ui_test::IntModelTest")
        {}

        IntModelTest::~IntModelTest()
        {}

        std::shared_ptr<IntModelTest> IntModelTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<IntModelTest>(new IntModelTest(context));
        }
                
        void IntModelTest::run()
        {
            if (auto context = _context.lock())
            {
                auto model = IntModel::create(context);

                int value = 0;
                RangeI range;
                bool hasDefaultValue = false;
                auto valueObserver = ValueObserver<int>::create(
                    model->observeValue(),
                    [&value](int v)
                    {
                        value = v;
                    });
                auto rangeObserver = ValueObserver<RangeI>::create(
                    model->observeRange(),
                    [&range](const RangeI& r)
                    {
                        range = r;
                    });
                auto defaultValueObserver = ValueObserver<bool>::create(
                    model->observeHasDefaultValue(),
                    [&hasDefaultValue](bool value)
                    {
                        hasDefaultValue = value;
                    });

                model->setValue(11);
                FTK_ASSERT(11 == model->getValue());
                FTK_ASSERT(11 == value);

                model->setRange(RangeI(0, 10));
                FTK_ASSERT(RangeI(0, 10) == model->getRange());
                FTK_ASSERT(RangeI(0, 10) == range);
                FTK_ASSERT(10 == value);

                model->setStep(2);
                FTK_ASSERT(2 == model->getStep());
                model->decrementStep();
                FTK_ASSERT(8 == value);
                model->incrementStep();
                FTK_ASSERT(10 == value);

                model->setLargeStep(5);
                FTK_ASSERT(5 == model->getLargeStep());
                model->decrementLargeStep();
                FTK_ASSERT(5 == value);
                model->incrementLargeStep();
                FTK_ASSERT(10 == value);

                model->setDefaultValue(0);
                FTK_ASSERT(0 == model->getDefaultValue());
                FTK_ASSERT(hasDefaultValue);
                model->setDefaultValue();
                FTK_ASSERT(0 == value);
                model->clearDefaultValue();
                FTK_ASSERT(!hasDefaultValue);
            }
        }
    }
}

