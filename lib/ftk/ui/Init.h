// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <memory>
#include <string>

namespace ftk
{
    class Context;

    //! Initialize the UI library.
    void uiInit(const std::shared_ptr<Context>&);
}

