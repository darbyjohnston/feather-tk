// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#include <ftk/Core/File.h>

#include <ftk/Core/Error.h>
#include <ftk/Core/String.h>

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

