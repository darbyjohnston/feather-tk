// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/DrawUtil.h>

#include <feather-tk/core/Math.h>

namespace feather_tk
{
    TriMesh2F rect(
        const Box2I& box,
        int cornerRadius,
        size_t resolution)
    {
        TriMesh2F out;

        const int x = box.x();
        const int y = box.y();
        const int w = box.w();
        const int h = box.h();

        if (0 == cornerRadius)
        {
            out.v.push_back(V2F(x, y));
            out.v.push_back(V2F(x + w, y));
            out.v.push_back(V2F(x + w, y + h));
            out.v.push_back(V2F(x, y + h));

            out.triangles.push_back(Triangle2({ 1, 2, 3 }));
            out.triangles.push_back(Triangle2({ 3, 4, 1 }));
        }
        else
        {
            const int r = cornerRadius;

            const std::vector<V2F> c =
            {
                V2F(x + w - r, y + h - r),
                V2F(x + r, y + h - r),
                V2F(x + r, y + r),
                V2F(x + w - r, y + r)
            };
            size_t i = 0;
            for (size_t j = 0; j < 4; ++j)
            {
                out.v.push_back(c[j]);
                for (size_t k = 0; k < resolution; ++k)
                {
                    const float v = k / static_cast<float>(resolution - 1);
                    const float a = lerp(v, j * 90.F, j * 90.F + 90.F);
                    const float cos = cosf(deg2rad(a));
                    const float sin = sinf(deg2rad(a));
                    out.v.push_back(V2F(
                        c[j].x + cos * r,
                        c[j].y + sin * r));
                }
                for (size_t k = 0; k < resolution - 1; ++k)
                {
                    out.triangles.push_back(Triangle2({ i + 1, i + k + 2, i + k + 3 }));
                }
                i += 1 + resolution;
            }

            i = 0;
            size_t j = resolution;
            out.triangles.push_back(Triangle2({ i + 1, j + 1, j + 2 }));
            out.triangles.push_back(Triangle2({ j + 1, j + 3, j + 2 }));

            i += 1 + resolution;
            j += 1 + resolution;
            out.triangles.push_back(Triangle2({ i + 1, j + 1, j + 2 }));
            out.triangles.push_back(Triangle2({ j + 1, j + 3, j + 2 }));

            i += 1 + resolution;
            j += 1 + resolution;
            out.triangles.push_back(Triangle2({ i + 1, j + 1, j + 2 }));
            out.triangles.push_back(Triangle2({ j + 1, j + 3, j + 2 }));

            i += 1 + resolution;
            j += 1 + resolution;
            out.triangles.push_back(Triangle2({ i + 1, j + 1, 2 }));
            out.triangles.push_back(Triangle2({ 2, 1, i + 1 }));

            i = 0;
            j = 1 + resolution;
            size_t k = (1 + resolution) * 2;
            out.triangles.push_back(Triangle2({ i + 1, j + 1, k + 1 }));
            i = k;
            j = k + 1 + resolution;
            k = 0;
            out.triangles.push_back(Triangle2({ i + 1, j + 1, k + 1 }));
        }

        return out;
    }

    TriMesh2F circle(
        const V2I& pos,
        int radius,
        size_t resolution)
    {
        TriMesh2F out;

        const int inc = 360 / resolution;
        for (int i = 0; i < 360; i += inc)
        {
            const size_t size = out.v.size();
            out.v.push_back(V2F(pos.x, pos.y));
            out.v.push_back(V2F(
                pos.x + cos(deg2rad(i)) * radius,
                pos.y + sin(deg2rad(i)) * radius));
            const int d = std::min(i + inc, 360);
            out.v.push_back(V2F(
                pos.x + cos(deg2rad(d)) * radius,
                pos.y + sin(deg2rad(d)) * radius));
            out.triangles.push_back({ size + 1, size + 2, size + 3 });
        }

        return out;
    }

    TriMesh2F border(
        const Box2I& box,
        int width,
        int radius,
        size_t resolution)
    {
        TriMesh2F out;

        const int x = box.x();
        const int y = box.y();
        const int w = box.w();
        const int h = box.h();

        if (0 == radius)
        {
            out.v.push_back(V2F(x, y));
            out.v.push_back(V2F(x + w, y));
            out.v.push_back(V2F(x + w, y + h));
            out.v.push_back(V2F(x, y + h));
            out.v.push_back(V2F(x + width, y + width));
            out.v.push_back(V2F(x + w - width, y + width));
            out.v.push_back(V2F(x + w - width, y + h - width));
            out.v.push_back(V2F(x + width, y + h - width));

            out.triangles.push_back(Triangle2({ 1, 2, 5 }));
            out.triangles.push_back(Triangle2({ 2, 6, 5 }));
            out.triangles.push_back(Triangle2({ 2, 3, 6 }));
            out.triangles.push_back(Triangle2({ 3, 7, 6 }));
            out.triangles.push_back(Triangle2({ 3, 4, 7 }));
            out.triangles.push_back(Triangle2({ 4, 8, 7 }));
            out.triangles.push_back(Triangle2({ 4, 1, 8 }));
            out.triangles.push_back(Triangle2({ 1, 5, 8 }));
        }
        else
        {
            const int r = radius;

            const std::vector<V2F> c =
            {
                V2F(x + w - r, y + h - r),
                V2F(x + r, y + h - r),
                V2F(x + r, y + r),
                V2F(x + w - r, y + r)
            };
            size_t i = 0;
            for (size_t j = 0; j < 4; ++j)
            {
                for (size_t k = 0; k < resolution; ++k)
                {
                    const float v = k / static_cast<float>(resolution - 1);
                    const float a = lerp(v, j * 90.F, j * 90.F + 90.F);
                    const float cos = cosf(deg2rad(a));
                    const float sin = sinf(deg2rad(a));
                    out.v.push_back(V2F(
                        c[j].x + cos * r,
                        c[j].y + sin * r));
                    out.v.push_back(V2F(
                        c[j].x + cos * (r - width),
                        c[j].y + sin * (r - width)));
                }
                for (size_t k = 0; k < resolution - 1; ++k)
                {
                    out.triangles.push_back(Triangle2({ i + 1, i + 3, i + 2 }));
                    out.triangles.push_back(Triangle2({ i + 3, i + 4, i + 2 }));
                    i += 2;
                }
                i += 2;
            }

            i = resolution * 2 - 2;
            out.triangles.push_back(Triangle2({ i + 1, i + 3, i + 2 }));
            out.triangles.push_back(Triangle2({ i + 3, i + 4, i + 2 }));

            i = resolution * 4 - 2;
            out.triangles.push_back(Triangle2({ i + 1, i + 3, i + 2 }));
            out.triangles.push_back(Triangle2({ i + 3, i + 4, i + 2 }));

            i = resolution * 6 - 2;
            out.triangles.push_back(Triangle2({ i + 1, i + 3, i + 2 }));
            out.triangles.push_back(Triangle2({ i + 3, i + 4, i + 2 }));

            i = resolution * 8 - 2;
            out.triangles.push_back(Triangle2({ i + 1, 1, i + 2 }));
            out.triangles.push_back(Triangle2({ 1, 2, i + 2 }));
        }

        return out;
    }

    TriMesh2F shadow(
        const Box2I& box,
        int cornerRadius,
        const float alpha,
        size_t resolution)
    {
        TriMesh2F out;

        const int x = box.x();
        const int y = box.y();
        const int w = box.w();
        const int h = box.h();
        const int r = cornerRadius;

        out.c.push_back(V4F(0.F, 0.F, 0.F, alpha));
        out.c.push_back(V4F(0.F, 0.F, 0.F, 0.F));

        const std::vector<V2F> c =
        {
            V2F(x + w - r, y + h - r),
            V2F(x + r, y + h - r),
            V2F(x + r, y + r),
            V2F(x + w - r, y + r)
        };
        size_t i = 0;
        for (size_t j = 0; j < 4; ++j)
        {
            out.v.push_back(c[j]);
            for (size_t k = 0; k < resolution; ++k)
            {
                const float v = k / static_cast<float>(resolution - 1);
                const float a = lerp(v, j * 90.F, j * 90.F + 90.F);
                const float cos = cosf(deg2rad(a));
                const float sin = sinf(deg2rad(a));
                out.v.push_back(V2F(
                    c[j].x + cos * r,
                    c[j].y + sin * r));
            }
            for (size_t k = 0; k < resolution - 1; ++k)
            {
                out.triangles.push_back(Triangle2(
                    {
                        Vertex2(i + 1, 0, 1),
                        Vertex2(i + k + 2, 0, 2),
                        Vertex2(i + k + 3, 0, 2)
                    }));
            }
            i += 1 + resolution;
        }

        i = 0;
        size_t j = resolution;
        out.triangles.push_back(Triangle2(
            {
                Vertex2(i + 1, 0, 1),
                Vertex2(j + 1, 0, 2),
                Vertex2(j + 2, 0, 1)
            }));
        out.triangles.push_back(Triangle2(
            {
                Vertex2(j + 1, 0, 2),
                Vertex2(j + 3, 0, 2),
                Vertex2(j + 2, 0, 1)
            }));

        i += 1 + resolution;
        j += 1 + resolution;
        out.triangles.push_back(Triangle2(
            {
                Vertex2(i + 1, 0, 1),
                Vertex2(j + 1, 0, 2),
                Vertex2(j + 2, 0, 1)
            }));
        out.triangles.push_back(Triangle2(
            {
                Vertex2(j + 1, 0, 2),
                Vertex2(j + 3, 0, 2),
                Vertex2(j + 2, 0, 1)
            }));

        i += 1 + resolution;
        j += 1 + resolution;
        out.triangles.push_back(Triangle2(
            {
                Vertex2(i + 1, 0, 1),
                Vertex2(j + 1, 0, 2),
                Vertex2(j + 2, 0, 1)
            }));
        out.triangles.push_back(Triangle2(
            {
                Vertex2(j + 1, 0, 2),
                Vertex2(j + 3, 0, 2),
                Vertex2(j + 2, 0, 1)
            }));

        i += 1 + resolution;
        j += 1 + resolution;
        out.triangles.push_back(Triangle2(
            {
                Vertex2(i + 1, 0, 1),
                Vertex2(j + 1, 0, 2),
                Vertex2(2, 0, 2)
            }));
        out.triangles.push_back(Triangle2(
            {
                Vertex2(2, 0, 2),
                Vertex2(1, 0, 1),
                Vertex2(i + 1, 0, 1)
            }));

        i = 0;
        j = 1 + resolution;
        size_t k = (1 + resolution) * 2;
        out.triangles.push_back(Triangle2(
            {
                Vertex2(i + 1, 0, 1),
                Vertex2(j + 1, 0, 1),
                Vertex2(k + 1, 0, 1)
            }));
        i = k;
        j = k + 1 + resolution;
        k = 0;
        out.triangles.push_back(Triangle2(
            {
                Vertex2(i + 1, 0, 1),
                Vertex2(j + 1, 0, 1),
                Vertex2(k + 1, 0, 1)
            }));

        return out;
    }
}