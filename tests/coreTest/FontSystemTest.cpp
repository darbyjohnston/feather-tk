// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/FontSystemTest.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Context.h>
#include <feather-tk/core/FontSystem.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace core_test
    {
        FontSystemTest::FontSystemTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::core_test::FontSystemTest")
        {}

        FontSystemTest::~FontSystemTest()
        {}

        std::shared_ptr<FontSystemTest> FontSystemTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FontSystemTest>(new FontSystemTest(context));
        }
        
        void FontSystemTest::run()
        {
            {
                const FontInfo a;
                const FontInfo b("NotoSans-Bold", 16);
                FEATHER_TK_ASSERT(a == a);
                FEATHER_TK_ASSERT(a != b);
            }
            {
                const GlyphInfo a;
                const FontInfo fontInfo("NotoSans-Bold", 16);
                const GlyphInfo b(1, fontInfo);
                FEATHER_TK_ASSERT(a == a);
                FEATHER_TK_ASSERT(a != b);
                FEATHER_TK_ASSERT(a < b);
            }
            if (auto context = _context.lock())
            {
                auto fontSystem = context->getSystem<FontSystem>();

                FontInfo info;
                FontMetrics metrics = fontSystem->getMetrics(info);
                _print(Format("Metrics: ascender={0}, descender={1}, lineHeight={2}").
                    arg(metrics.ascender).
                    arg(metrics.descender).
                    arg(metrics.lineHeight));

                std::string s = "Hello\nworld";
                Size2I size = fontSystem->getSize(s, info);
                _print(Format("{0} size: {1}").arg(s).arg(size));
                auto boxes = fontSystem->getBox(s, info);
                auto glyphs = fontSystem->getGlyphs(s, info);

                size = fontSystem->getSize(s, info, 1);
                _print(Format("{0} size: {1}").arg(s).arg(size));
                boxes = fontSystem->getBox(s, info, 1);
                
                _print(Format("Glyph cache: {0} {1}%").
                    arg(fontSystem->getGlyphCacheSize()).
                    arg(fontSystem->getGlyphCachePercentage()));
            }
            if (auto context = _context.lock())
            {
                auto fontSystem = context->getSystem<FontSystem>();
                try
                {
                    fontSystem->addFont("", nullptr, 0);
                    FEATHER_TK_ASSERT(false);
                }
                catch (const std::exception&)
                {}
            }
        }
    }
}

