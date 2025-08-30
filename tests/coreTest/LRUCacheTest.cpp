// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/LRUCacheTest.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>
#include <feather-tk/core/LRUCache.h>

namespace ftk
{
    namespace core_test
    {
        LRUCacheTest::LRUCacheTest(const std::shared_ptr<Context>& context) :
            ITest(context, "ftk::core_test::LRUCacheTest")
        {}

        LRUCacheTest::~LRUCacheTest()
        {}

        std::shared_ptr<LRUCacheTest> LRUCacheTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<LRUCacheTest>(new LRUCacheTest(context));
        }
        
        void LRUCacheTest::run()
        {
            LRUCache<int, bool> c;
            c.setMax(3);
            c.setMax(3);
            FTK_ASSERT(3 == c.getMax());
            FTK_ASSERT(0 == c.getSize());
            FTK_ASSERT(0 == c.getCount());
            _print(Format("Percentage: {0}").arg(c.getPercentage()));
            
            c.add(0, true);
            _print(Format("Percentage: {0}").arg(c.getPercentage()));
            c.add(1, true);
            _print(Format("Percentage: {0}").arg(c.getPercentage()));
            c.add(2, true);
            _print(Format("Percentage: {0}").arg(c.getPercentage()));
            c.add(3, true);
            _print(Format("Percentage: {0}").arg(c.getPercentage()));
            FTK_ASSERT(3 == c.getSize());

            FTK_ASSERT(c.contains(2));
            bool v = false;
            FTK_ASSERT(c.get(2, v));
            FTK_ASSERT(v);
            FTK_ASSERT(!c.get(0, v));
            c.remove(2);
            FTK_ASSERT(!c.contains(2));
            c.clear();
            FTK_ASSERT(0 == c.getSize());
            
            c.add(0, true);
            c.add(1, true);
            c.add(2, true);
            c.add(3, true);
            FTK_ASSERT(1 == c.getKeys()[0]);
            FTK_ASSERT(2 == c.getKeys()[1]);
            FTK_ASSERT(3 == c.getKeys()[2]);
            FTK_ASSERT(c.getValues()[0]);
            FTK_ASSERT(c.getValues()[1]);
            FTK_ASSERT(c.getValues()[2]);
            
            c.setMax(2);
            FTK_ASSERT(2 == c.getSize());
        }
    }
}

