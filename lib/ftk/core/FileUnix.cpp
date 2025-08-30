// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/core/File.h>

#if defined(__APPLE__)
#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CFBundle.h>
#include <CoreServices/CoreServices.h>
#endif // __APPLE__

#include <cstring>
#include <filesystem>

#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

namespace ftk
{
    std::filesystem::path getUserPath(UserPath value)
    {
        std::filesystem::path out;
#if defined(__APPLE__)
        OSType folderType = kDesktopFolderType;
        switch (value)
        {
        case UserPath::Home:      folderType = kCurrentUserFolderType; break;
        case UserPath::Desktop:   folderType = kDesktopFolderType;     break;
        case UserPath::Documents: folderType = kDocumentsFolderType;   break;
        case UserPath::Downloads: folderType = kCurrentUserFolderType; break;
        default: break;
        }
        FSRef ref;
        FSFindFolder(kUserDomain, folderType, kCreateFolder, &ref);
        char path[PATH_MAX];
        FSRefMakePath(&ref, (UInt8*)&path, PATH_MAX);
        if (UserPath::Downloads == value)
        {
            out = std::filesystem::path(path) / std::filesystem::path("Downloads");
        }
        else
        {
            out = path;
        }
#else // __APPLE__
        if (struct passwd* buf = ::getpwuid(::getuid()))
        {
            switch (value)
            {
            case UserPath::Home:
                out = std::filesystem::path(buf->pw_dir);
                break;
            case UserPath::Desktop:
                out = std::filesystem::path(buf->pw_dir) / std::filesystem::path("Desktop");
                break;
            case UserPath::Documents:
                out = std::filesystem::path(buf->pw_dir) / std::filesystem::path("Documents");
                break;
            case UserPath::Downloads:
                out = std::filesystem::path(buf->pw_dir) / std::filesystem::path("Downloads");
                break;
            default: break;
            }
        }
#endif // __APPLE__
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
