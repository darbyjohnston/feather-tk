// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <ftk/Core/Util.h>

#include <filesystem>
#include <iostream>
#include <vector>

namespace ftk
{
    //! \name Files
    ///@{

    //! Does the file name start with a dot?
    bool isDotFile(const std::string&);

    //! Split a path.
    std::vector<std::string> split(std::filesystem::path);

    //! Get the list of file system drives.
    std::vector<std::filesystem::path> getDrives();

    //! User paths.
    enum class UserPath
    {
        Home,
        Desktop,
        Documents,
        Downloads,

        Count,
        First = Home
    };
    FTK_ENUM(UserPath);

    //! Get a user path.
    std::filesystem::path getUserPath(UserPath);
        
    ///@}
}
