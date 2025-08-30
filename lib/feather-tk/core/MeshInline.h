// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

namespace ftk
{
    constexpr Vertex2::Vertex2(size_t v, size_t t, size_t c) :
        v(v),
        t(t),
        c(c)
    {}

    constexpr Vertex3::Vertex3(size_t v, size_t t, size_t n, size_t c) :
        v(v),
        t(t),
        n(n),
        c(c)
    {}

    inline float edge(const V2F& p, const V2F& v0, const V2F& v1)
    {
        return
            (p.x - v0.x) * (v1.y - v0.y) -
            (p.y - v0.y) * (v1.x - v0.x);
    }
}
