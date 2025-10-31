// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#include <ftk/Core/OS.h>

#include <ftk/Core/String.h>

namespace ftk
{
    bool getEnv(const std::string& name, int& out)
    {
        std::string value;
        if (getEnv(name, value))
        {
            out = !value.empty() ? std::stoi(value) : 0;
            return true;
        }
        return false;
    }

    bool getEnv(const std::string& name, std::vector<std::string>& out)
    {
        std::string value;
        if (getEnv(name, value))
        {
            out = split(value, envListSeparator);
            return true;
        }
        return false;
    }
}