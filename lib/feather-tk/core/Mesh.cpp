// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/core/Mesh.h>

#include <feather-tk/core/Math.h>

namespace feather_tk
{
    TriMesh2F mesh(const Box2I& box, bool flipV)
    {
        TriMesh2F out;

        const auto& min = box.min;
        const auto& max = box.max;
        out.v.push_back(V2F(min.x, min.y));
        out.v.push_back(V2F(max.x + 1, min.y));
        out.v.push_back(V2F(max.x + 1, max.y + 1));
        out.v.push_back(V2F(min.x, max.y + 1));
        out.t.push_back(V2F(0.F, flipV ? 1.F : 0.F));
        out.t.push_back(V2F(1.F, flipV ? 1.F : 0.F));
        out.t.push_back(V2F(1.F, flipV ? 0.F : 1.F));
        out.t.push_back(V2F(0.F, flipV ? 0.F : 1.F));

        Triangle2 triangle;
        triangle.v[0].v = 1;
        triangle.v[1].v = 2;
        triangle.v[2].v = 3;
        triangle.v[0].t = 1;
        triangle.v[1].t = 2;
        triangle.v[2].t = 3;
        out.triangles.push_back(triangle);
        triangle.v[0].v = 3;
        triangle.v[1].v = 4;
        triangle.v[2].v = 1;
        triangle.v[0].t = 3;
        triangle.v[1].t = 4;
        triangle.v[2].t = 1;
        out.triangles.push_back(triangle);

        return out;
    }

    TriMesh2F mesh(const Box2F& box, bool flipV)
    {
        TriMesh2F out;

        const auto& min = box.min;
        const auto& max = box.max;
        out.v.push_back(V2F(min.x, min.y));
        out.v.push_back(V2F(max.x, min.y));
        out.v.push_back(V2F(max.x, max.y));
        out.v.push_back(V2F(min.x, max.y));
        out.t.push_back(V2F(0.F, flipV ? 1.F : 0.F));
        out.t.push_back(V2F(1.F, flipV ? 1.F : 0.F));
        out.t.push_back(V2F(1.F, flipV ? 0.F : 1.F));
        out.t.push_back(V2F(0.F, flipV ? 0.F : 1.F));

        Triangle2 triangle;
        triangle.v[0].v = 1;
        triangle.v[1].v = 2;
        triangle.v[2].v = 3;
        triangle.v[0].t = 1;
        triangle.v[1].t = 2;
        triangle.v[2].t = 3;
        out.triangles.push_back(triangle);
        triangle.v[0].v = 3;
        triangle.v[1].v = 4;
        triangle.v[2].v = 1;
        triangle.v[0].t = 3;
        triangle.v[1].t = 4;
        triangle.v[2].t = 1;
        out.triangles.push_back(triangle);

        return out;
    }

    TriMesh2F checkers(
        const Box2I& box,
        const Color4F& color0,
        const Color4F& color1,
        const Size2I& checkerSize)
    {
        TriMesh2F out;

        // X points.
        std::vector<int> xs;
        int x = box.min.x;
        for (; x < box.max.x; x += checkerSize.w)
        {
            xs.push_back(x);
        }
        if (x >= box.max.x)
        {
            xs.push_back(box.max.x);
        }

        // Y points.
        std::vector<int> ys;
        int y = box.min.y;
        for (; y < box.max.y; y += checkerSize.h)
        {
            ys.push_back(y);
        }
        if (y >= box.max.y)
        {
            ys.push_back(box.max.y);
        }

        if (!xs.empty() && !ys.empty())
        {
            // 2D points.
            for (int j = 0; j < ys.size(); ++j)
            {
                for (int i = 0; i < xs.size(); ++i)
                {
                    out.v.push_back(V2F(xs[i], ys[j]));
                }
            }

            // Colors.
            out.c.push_back(V4F(color0.r, color0.g, color0.b, color0.a));
            out.c.push_back(V4F(color1.r, color1.g, color1.b, color1.a));

            // Triangles.
            for (int j = 0; j < ys.size() - 1; ++j)
            {
                for (int i = 0; i < xs.size() - 1; ++i)
                {
                    const int v0 = j * xs.size() + i + 1;
                    const int v1 = j * xs.size() + (i + 1) + 1;
                    const int v2 = (j + 1) * xs.size() + (i + 1) + 1;
                    const int v3 = (j + 1) * xs.size() + i + 1;
                    const int c = (j + i) % 2 + 1;
                    out.triangles.push_back({
                        Vertex2(v0, 0, c),
                        Vertex2(v1, 0, c),
                        Vertex2(v2, 0, c) });
                    out.triangles.push_back({
                        Vertex2(v2, 0, c),
                        Vertex2(v3, 0, c),
                        Vertex2(v0, 0, c) });
                }
            }
        }

        return out;
    }

    TriMesh3F sphere(
        float radius,
        size_t xResolution,
        size_t yResolution)
    {
        TriMesh3F out;

        //! \bug Use only a single vertex at each pole.
        for (size_t v = 0; v <= yResolution; ++v)
        {
            const float v1 = static_cast<float>(v) / static_cast<float>(yResolution);

            for (size_t u = 0; u <= xResolution; ++u)
            {
                const float u1 = static_cast<float>(u) / static_cast<float>(xResolution);
                const float x = radius * sinf(v1 * pi) * cosf(u1 * pi2);
                const float y = radius * cosf(v1 * pi);
                const float z = radius * sinf(v1 * pi) * sinf(u1 * pi2);
                out.v.push_back(V3F(x, y, z));
                out.t.push_back(V2F(u1, 1.F - v1));
            }
        }

        Triangle3 triangle;
        for (size_t v = 0; v < yResolution; ++v)
        {
            for (size_t u = 0; u < xResolution; ++u)
            {
                const size_t i = u + v * (xResolution + 1);
                const size_t j = u + (v + 1) * (xResolution + 1);
                triangle.v[0].v = triangle.v[0].t = j + 1 + 1;
                triangle.v[1].v = triangle.v[1].t = j + 1;
                triangle.v[2].v = triangle.v[2].t = i + 1;
                out.triangles.push_back(triangle);
                triangle.v[0].v = triangle.v[0].t = i + 1;
                triangle.v[1].v = triangle.v[1].t = i + 1 + 1;
                triangle.v[2].v = triangle.v[2].t = j + 1 + 1;
                out.triangles.push_back(triangle);
            }
        }

        return out;
    }
}