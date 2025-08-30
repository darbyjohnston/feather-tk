// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/StringTest.h>

#include <ftk/core/Assert.h>
#include <ftk/core/String.h>

namespace ftk
{
    namespace core_test
    {
        StringTest::StringTest(const std::shared_ptr<Context>& context) :
            ITest(context, "ftk::core_test::StringTest")
        {}

        StringTest::~StringTest()
        {}

        std::shared_ptr<StringTest> StringTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<StringTest>(new StringTest(context));
        }
        
        void StringTest::run()
        {
            _split();
            _format();
            _compare();
            _convert();
            _filler();
        }
        
        void StringTest::_split()
        {
            {
                FTK_ASSERT(
                    split("a,b,c", ',') ==
                    std::vector<std::string>({ "a", "b", "c" }));
                FTK_ASSERT(
                    split("a,,c", ',', SplitOptions::DiscardEmpty) ==
                    std::vector<std::string>({ "a", "c" }));
                FTK_ASSERT(
                    split("a,,c", ',', SplitOptions::KeepEmpty) ==
                    std::vector<std::string>({ "a", "", "c" }));
            }
            {
                FTK_ASSERT(
                    split("a,b.c", { ',', '.' } ) ==
                    std::vector<std::string>({ "a", "b", "c" }));
                FTK_ASSERT(
                    split("a,.c", { ',', '.' }, SplitOptions::DiscardEmpty) ==
                    std::vector<std::string>({ "a", "c" }));
                FTK_ASSERT(
                    split("a,.c", { ',', '.' }, SplitOptions::KeepEmpty) ==
                    std::vector<std::string>({ "a", "", "c" }));
            }
            {
                FTK_ASSERT(join({ "a", "b", "c" }, ',') == "a,b,c");
                FTK_ASSERT(join({ "a", "b", "c" }, ",.") == "a,.b,.c");
            }
        }
        
        void StringTest::_format()
        {
            {
                FTK_ASSERT(toUpper("abc") == "ABC");
                FTK_ASSERT(toLower("ABC") == "abc");
            }
            {
                std::string s = "abc";
                removeTrailingNewlines(s);
                FTK_ASSERT("abc" == s);
                s = "abc\n";
                removeTrailingNewlines(s);
                FTK_ASSERT("abc" == s);
                s = "abc\n\r";
                removeTrailingNewlines(s);
                FTK_ASSERT("abc" == s);
            }
            {
                const std::string s("abcdef");
                FTK_ASSERT("abcdef" == elide(s, 6));
                FTK_ASSERT("abc..." == elide(s, 3));
                FTK_ASSERT("..." == elide(s, 0));
            }
        }
        
        void StringTest::_compare()
        {
            {
                FTK_ASSERT(!compare("abc", "ABC", CaseCompare::Sensitive));
                FTK_ASSERT(compare("abc", "ABC", CaseCompare::Insensitive));
            }
            {
                FTK_ASSERT(!contains("abc", "AB", CaseCompare::Sensitive));
                FTK_ASSERT(contains("abc", "AB", CaseCompare::Insensitive));
            }
        }
        
        void StringTest::_convert()
        {
            {
                const std::string s("abc");
                const std::wstring w = toWide(s);
                FTK_ASSERT(s == fromWide(w));
            }
        }

        void StringTest::_filler()
        {
            {
                _print(getLoremIpsum(100));
            }
        }
    }
}

