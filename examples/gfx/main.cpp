// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#include "App.h"

FTK_MAIN()
{
    try
    {
        auto context = ftk::Context::create();
        auto app = gfx::App::create(context, ftk::convert(argc, argv));
        if (app->getExit() != 0)
            return app->getExit();
        app->run();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
