// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <memory>
#include <string>

namespace ftk
{
    class Context;

    //! Initialize the UI library.
    void uiInit(const std::shared_ptr<Context>&);
}

