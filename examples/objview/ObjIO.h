// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <ftk/Core/Mesh.h>

#include <filesystem>

namespace objview
{
    //! \todo This is a simplified .obj reader, it currently only handles:
    //! * vertices
    //! * texture vertices
    //! * normals
    //! * faces
    std::shared_ptr<ftk::TriMesh3F> read(const std::filesystem::path&);
}
