// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/core/File.h>

#include <feather-tk/core/Error.h>
#include <feather-tk/core/String.h>

#include <algorithm>
#include <array>
#include <list>
#include <sstream>

namespace ftk
{
    FTK_ENUM_IMPL(
        UserPath,
        "Home",
        "Desktop",
        "Documents",
        "Downloads");

    bool isDotFile(const std::string& fileName)
    {
        return !fileName.empty() && '.' == fileName[0];
    }

    std::vector<std::string> split(std::filesystem::path path)
    {
        std::list<std::string> out;
        const std::filesystem::path root = path.root_path();
        while (!path.empty() && path != root)
        {
            if (!path.filename().empty())
            {
                out.push_front(path.filename().u8string());
            }
            path = path.parent_path();
        }
        if (!path.empty())
        {
            out.push_front(path.u8string());
        }
        return std::vector<std::string>(out.begin(), out.end());
    }
}

