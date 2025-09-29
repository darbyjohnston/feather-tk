// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "App.h"

#include <iostream>

int main(int argc, char** argv)
{
    int r = 0;
    try
    {
        auto app = App::create(argc, argv);
        r = app->getExit();
        if (0 == r)
        {
            app->run();
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    return r;
}

