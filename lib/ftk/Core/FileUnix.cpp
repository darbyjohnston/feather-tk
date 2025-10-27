// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/Core/File.h>

#include <cstdlib>

namespace ftk
{
    std::filesystem::path getUserPath(UserPath value)
    {
        std::filesystem::path out;
        const std::filesystem::path home = std::getenv("HOME");
        switch (value)
        {
        case UserPath::Home:      out = home; break;
        case UserPath::Desktop:   out = home / "Desktop";   break;
        case UserPath::Documents: out = home / "Documents"; break;
        case UserPath::Downloads: out = home / "Downloads"; break;
        default: break;
        }
        return out;
    }

    std::vector<std::filesystem::path> getDrives()
    {
        std::vector<std::filesystem::path> out;
        out.push_back(std::filesystem::path("/"));
#if defined(__APPLE__)
        for (const auto& i : std::filesystem::directory_iterator("/Volumes"))
        {
            out.push_back(i.path());
        }
#else // __APPLE__
        for (const auto& i : std::filesystem::directory_iterator("/mnt"))
        {
            out.push_back(i.path());
        }
#endif // __APPLE__
        return out;
    }
}
