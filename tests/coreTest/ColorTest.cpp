// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/ColorTest.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Color.h>
#include <feather-tk/core/Format.h>

#include <sstream>

namespace feather_tk
{
    namespace core_test
    {
        ColorTest::ColorTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::core_test::ColorTest")
        {}

        ColorTest::~ColorTest()
        {}

        std::shared_ptr<ColorTest> ColorTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ColorTest>(new ColorTest(context));
        }
        
        void ColorTest::run()
        {
            _members();
            _operators();
            _functions();
            _serialize();
        }
        
        void ColorTest::_members()
        {
            {
                const Color<5, float> c;
                FEATHER_TK_ASSERT(c[0] == 0.F);
                FEATHER_TK_ASSERT(c[1] == 0.F);
                FEATHER_TK_ASSERT(c[2] == 0.F);
                FEATHER_TK_ASSERT(c[3] == 0.F);
                FEATHER_TK_ASSERT(c[4] == 0.F);
                FEATHER_TK_ASSERT(c.data());
            }
            {
                Color<5, float> c;
                c[0] = .1F;
                c[1] = .2F;
                c[2] = .3F;
                c[3] = .4F;
                c[4] = .5F;
                FEATHER_TK_ASSERT(c[0] == .1F);
                FEATHER_TK_ASSERT(c[1] == .2F);
                FEATHER_TK_ASSERT(c[2] == .3F);
                FEATHER_TK_ASSERT(c[3] == .4F);
                FEATHER_TK_ASSERT(c[4] == .5F);
                FEATHER_TK_ASSERT(c.data());
            }
            {
                const Color1F c1;
                FEATHER_TK_ASSERT(c1[0] == 0.F);
                FEATHER_TK_ASSERT(c1.data());
                const Color2F c2;
                FEATHER_TK_ASSERT(c2[0] == 0.F);
                FEATHER_TK_ASSERT(c2[1] == 0.F);
                FEATHER_TK_ASSERT(c2.data());
                const Color3F c3;
                FEATHER_TK_ASSERT(c3[0] == 0.F);
                FEATHER_TK_ASSERT(c3[1] == 0.F);
                FEATHER_TK_ASSERT(c3[2] == 0.F);
                FEATHER_TK_ASSERT(c3.data());
                const Color4F c4;
                FEATHER_TK_ASSERT(c4[0] == 0.F);
                FEATHER_TK_ASSERT(c4[1] == 0.F);
                FEATHER_TK_ASSERT(c4[2] == 0.F);
                FEATHER_TK_ASSERT(c4[3] == 0.F);
                FEATHER_TK_ASSERT(c4.data());
            }
            {
                const Color1F c1(1.F);
                FEATHER_TK_ASSERT(c1.l == 1.F);
                const Color2F c2(1.F, 1.F);
                FEATHER_TK_ASSERT(c2.l == 1.F);
                FEATHER_TK_ASSERT(c2.a == 1.F);
                const Color3F c3(1.F, 1.F, 1.F);
                FEATHER_TK_ASSERT(c3.r == 1.F);
                FEATHER_TK_ASSERT(c3.g == 1.F);
                FEATHER_TK_ASSERT(c3.b == 1.F);
                const Color4F c4(1.F, 1.F, 1.F, 1.F);
                FEATHER_TK_ASSERT(c4.r == 1.F);
                FEATHER_TK_ASSERT(c4.g == 1.F);
                FEATHER_TK_ASSERT(c4.b == 1.F);
                FEATHER_TK_ASSERT(c4.a == 1.F);
            }
            {
                Color1F c1;
                c1[0] = 1.F;
                FEATHER_TK_ASSERT(c1[0] == 1.F);
                Color2F c2;
                c2[0] = 1.F;
                FEATHER_TK_ASSERT(c2[0] == 1.F);
                Color3F c3;
                c3[0] = 1.F;
                FEATHER_TK_ASSERT(c3[0] == 1.F);
                Color4F c4;
                c4[0] = 1.F;
                FEATHER_TK_ASSERT(c4[0] == 1.F);
            }
        }
        
        void ColorTest::_operators()
        {
            {
                const Color1F c(.5F);
                FEATHER_TK_ASSERT(c == Color1F(.5F));
                FEATHER_TK_ASSERT(c != Color1F(1.F));
            }
        }

        void ColorTest::_functions()
        {
            {
                Color1F c(.5F);
                _print(Format("{0} lighter: {1}").arg(c).arg(lighter(c, .1F)));
                _print(Format("{0} darker: {1}").arg(c).arg(darker(c, .1F)));
            }
            {
                Color2F c(.5F);
                _print(Format("{0} lighter: {1}").arg(c).arg(lighter(c, .1F)));
                _print(Format("{0} darker: {1}").arg(c).arg(darker(c, .1F)));
            }
            {
                Color3F c(.5F, .5F, .5F);
                _print(Format("{0} lighter: {1}").arg(c).arg(lighter(c, .1F)));
                _print(Format("{0} darker: {1}").arg(c).arg(darker(c, .1F)));
            }
            {
                Color4F c(.5F, .5F, .5F);
                _print(Format("{0} lighter: {1}").arg(c).arg(lighter(c, .1F)));
                _print(Format("{0} darker: {1}").arg(c).arg(darker(c, .1F)));
            }
            {
                Color3F c(.4F, .5F, .6F);
                _print(Format("{0} greyscale: {1}").arg(c).arg(greyscale(c)));
            }
            {
                Color4F c(.4F, .5F, .6F);
                _print(Format("{0} greyscale: {1}").arg(c).arg(greyscale(c)));
            }
            {
                const V3F v(1.F, 0.F, 0.F);
                const auto m = brightness(V3F(2.F, 2.F, 2.F));
                _print(Format("{0} brightness: {1}").arg(v).arg(v * m));
            }
            {
                const V3F v(1.F, 0.F, 0.F);
                const auto m = contrast(V3F(.5F, .5F, .5F));
                _print(Format("{0} contrast: {1}").arg(v).arg(v * m));
            }
            {
                const V3F v(1.F, 0.F, 0.F);
                const auto m = saturation(V3F(.5F, .5F, .5F));
                _print(Format("{0} saturation: {1}").arg(v).arg(v * m));
            }
            {
                const V3F v(1.F, 0.F, 0.F);
                auto m = tint(.0F);
                _print(Format("{0} tint: {1}").arg(v).arg(v * m));
                m = tint(.2F);
                _print(Format("{0} tint: {1}").arg(v).arg(v * m));
                m = tint(.4F);
                _print(Format("{0} tint: {1}").arg(v).arg(v * m));
                m = tint(.6F);
                _print(Format("{0} tint: {1}").arg(v).arg(v * m));
                m = tint(.8F);
                _print(Format("{0} tint: {1}").arg(v).arg(v * m));
                m = tint(1.F);
                _print(Format("{0} tint: {1}").arg(v).arg(v * m));
            }
        }

        void ColorTest::_serialize()
        {
            {
                const Color1F c(.5F);
                nlohmann::json json;
                to_json(json, c);
                Color1F c2;
                from_json(json, c2);
                FEATHER_TK_ASSERT(c == c2);
            }
            {
                const Color2F c(.5F);
                nlohmann::json json;
                to_json(json, c);
                Color2F c2;
                from_json(json, c2);
                FEATHER_TK_ASSERT(c == c2);
            }
            {
                const Color3F c(.4F, .5F, .6F);
                nlohmann::json json;
                to_json(json, c);
                Color3F c2;
                from_json(json, c2);
                FEATHER_TK_ASSERT(c == c2);
            }
            {
                const Color4F c(.4F, .5F, .6F);
                nlohmann::json json;
                to_json(json, c);
                Color4F c2;
                from_json(json, c2);
                FEATHER_TK_ASSERT(c == c2);
            }
            {
                const Color1F c(.5F);
                std::stringstream ss;
                ss << c;
                Color1F c1;
                ss >> c1;
                FEATHER_TK_ASSERT(c == c1);
            }
            {
                const Color2F c(.5F, 1.F);
                std::stringstream ss;
                ss << c;
                Color2F c1;
                ss >> c1;
                FEATHER_TK_ASSERT(c == c1);
            }
            {
                const Color3F c(.25F, .5F, .75F);
                std::stringstream ss;
                ss << c;
                Color3F c1;
                ss >> c1;
                FEATHER_TK_ASSERT(c == c1);
            }
            {
                const Color4F c(.25F, .5F, .75F, 1.F);
                std::stringstream ss;
                ss << c;
                Color4F c1;
                ss >> c1;
                FEATHER_TK_ASSERT(c == c1);
            }
        }
    }
}

