// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <CoreTest/FileTest.h>

#include <ftk/Core/Assert.h>
#include <ftk/Core/File.h>
#include <ftk/Core/Format.h>

namespace ftk
{
    namespace core_test
    {
        FileTest::FileTest(const std::shared_ptr<Context>& context) :
            ITest(context, "ftk::core_test::FileTest")
        {}

        FileTest::~FileTest()
        {}

        std::shared_ptr<FileTest> FileTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FileTest>(new FileTest(context));
        }
        
        void FileTest::run()
        {
            _util();
            _split();
            _drives();
            _userPaths();
        }

        void FileTest::_util()
        {
            FTK_ASSERT(!isDotFile(""));
            FTK_ASSERT(!isDotFile("login"));
            FTK_ASSERT(isDotFile(".login"));
            FTK_ASSERT(isDotFile("."));
            FTK_ASSERT(isDotFile(".."));
        }

        void FileTest::_split()
        {
            {
                const std::vector<std::string> pieces = split("");
                FTK_ASSERT(pieces.empty());
            }
            {
                const std::vector<std::string> pieces = split("/");
                FTK_ASSERT(1 == pieces.size());
                FTK_ASSERT("/" == pieces[0]);
            }
            {
                const std::vector<std::string> pieces = split("a");
                FTK_ASSERT(1 == pieces.size());
                FTK_ASSERT("a" == pieces[0]);
            }
            {
                const std::vector<std::string> pieces = split("/a");
                FTK_ASSERT(2 == pieces.size());
                FTK_ASSERT("/" == pieces[0]);
                FTK_ASSERT("a" == pieces[1]);
            }
            {
                const std::vector<std::string> pieces = split("/a/b/c");
                FTK_ASSERT(4 == pieces.size());
                FTK_ASSERT("/" == pieces[0]);
                FTK_ASSERT("a" == pieces[1]);
                FTK_ASSERT("b" == pieces[2]);
                FTK_ASSERT("c" == pieces[3]);
            }
            {
                const std::vector<std::string> pieces = split("/a/b/c/");
                FTK_ASSERT(4 == pieces.size());
                FTK_ASSERT("/" == pieces[0]);
                FTK_ASSERT("a" == pieces[1]);
                FTK_ASSERT("b" == pieces[2]);
                FTK_ASSERT("c" == pieces[3]);
            }
            {
                const std::vector<std::string> pieces = split("a/b/c/");
                FTK_ASSERT(3 == pieces.size());
                FTK_ASSERT("a" == pieces[0]);
                FTK_ASSERT("b" == pieces[1]);
                FTK_ASSERT("c" == pieces[2]);
            }
#if defined(_WINDOWS)
            {
                const std::vector<std::string> pieces = split("c:");
                FTK_ASSERT(1 == pieces.size());
                FTK_ASSERT("c:" == pieces[0]);
            }
            {
                const std::vector<std::string> pieces = split("c:\\");
                FTK_ASSERT(1 == pieces.size());
                FTK_ASSERT("c:\\" == pieces[0]);
            }
            {
                const std::vector<std::string> pieces = split("c:\\a");
                FTK_ASSERT(2 == pieces.size());
                FTK_ASSERT("c:\\" == pieces[0]);
                FTK_ASSERT("a" == pieces[1]);
            }
#endif // _WINDOWS
        }

        void FileTest::_drives()
        {
            for (const auto& drive : getDrives())
            {
                _print(Format("Drive: {0}").arg(drive));
            }
        }

        void FileTest::_userPaths()
        {
            for (auto path : getUserPathEnums())
            {
                _print(Format("{0}: {1}").arg(path).arg(getUserPath(path)));
            }
        }
    }
}

