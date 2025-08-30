// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/core/Color.h>
#include <ftk/core/Image.h>
#include <ftk/core/Mesh.h>

namespace ftk
{
    //! \name Drawing
    ///@{
        
    //! Create a mesh for drawing a rectangle.
    TriMesh2F rect(
        const Box2I&,
        int cornerRadius = 0,
        size_t resolution = 8);

    //! Create a mesh for drawing a circle.
    TriMesh2F circle(
        const V2I&,
        int radius,
        size_t resolution = 120);

    //! Create a mesh for drawing a border.
    TriMesh2F border(
        const Box2I&,
        int width,
        int radius = 0,
        size_t resolution = 8);

    //! Create a mesh for drawing a shadow.
    TriMesh2F shadow(
        const Box2I&,
        int cornerRadius,
        const float alpha = .2F,
        size_t resolution = 8);
        
    ///@}
}
