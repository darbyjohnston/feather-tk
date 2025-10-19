// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/Core/Mesh.h>

#include <filesystem>

namespace examples
{
    namespace objview
    {
        std::shared_ptr<ftk::TriMesh3F> read(const std::filesystem::path&);
    }
}