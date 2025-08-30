// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/RangeTest.h>

#include <ftk/core/Assert.h>
#include <ftk/core/Range.h>

#include <sstream>

namespace ftk
{
    namespace core_test
    {
        RangeTest::RangeTest(const std::shared_ptr<Context>& context) :
            ITest(context, "ftk::core_test::RangeTest")
        {}

        RangeTest::~RangeTest()
        {}

        std::shared_ptr<RangeTest> RangeTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<RangeTest>(new RangeTest(context));
        }
        
        void RangeTest::run()
        {
            _members();
            _functions();
            _serialize();
        }
        
        void RangeTest::_members()
        {
            {
                const RangeI r;
                FTK_ASSERT(0 == r.min());
                FTK_ASSERT(0 == r.max());
            }
            {
                const RangeI r(1, 2);
                FTK_ASSERT(1 == r.min());
                FTK_ASSERT(2 == r.max());
            }
            {
                const RangeI a;
                RangeI b;
                FTK_ASSERT(a == b);
                b = RangeI(1, 2);
                FTK_ASSERT(a != b);
                FTK_ASSERT(a < b);
            }
        }
        
        void RangeTest::_functions()
        {
            {
                FTK_ASSERT(contains(RangeI(0, 2), 1));
                FTK_ASSERT(!contains(RangeI(0, 2), 3));
            }
            {
                FTK_ASSERT(intersects(RangeI(0, 2), RangeI(1, 3)));
                FTK_ASSERT(!intersects(RangeI(0, 2), RangeI(3, 4)));
            }
            {
                FTK_ASSERT(expand(RangeI(), 2) == RangeI(0, 2));
                FTK_ASSERT(expand(RangeI(0, 2), RangeI(1, 3)) == RangeI(0, 3));
            }
        }

        void RangeTest::_serialize()
        {
            {
                const RangeI r(1, 2);
                nlohmann::json json;
                to_json(json, r);
                RangeI r2;
                from_json(json, r2);
                FTK_ASSERT(r == r2);
            }
            {
                const RangeSizeT r(1, 2);
                nlohmann::json json;
                to_json(json, r);
                RangeSizeT r2;
                from_json(json, r2);
                FTK_ASSERT(r == r2);
            }
            {
                const RangeF r(1.F, 2.F);
                nlohmann::json json;
                to_json(json, r);
                RangeF r2;
                from_json(json, r2);
                FTK_ASSERT(r == r2);
            }
            {
                const RangeD r(1.0, 2.0);
                nlohmann::json json;
                to_json(json, r);
                RangeD r2;
                from_json(json, r2);
                FTK_ASSERT(r == r2);
            }
            {
                const RangeI r(1, 2);
                std::stringstream ss;
                ss << r;
                RangeI r1;
                ss >> r1;
                FTK_ASSERT(r == r1);
            }
            {
                const RangeSizeT r(1, 2);
                std::stringstream ss;
                ss << r;
                RangeSizeT r1;
                ss >> r1;
                FTK_ASSERT(r == r1);
            }
            {
                const RangeF r(1.F, 2.F);
                std::stringstream ss;
                ss << r;
                RangeF r1;
                ss >> r1;
                FTK_ASSERT(r == r1);
            }
            {
                const RangeD r(1.0, 2.0);
                std::stringstream ss;
                ss << r;
                RangeD r1;
                ss >> r1;
                FTK_ASSERT(r == r1);
            }
        }
    }
}

