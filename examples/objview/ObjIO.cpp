// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "ObjIO.h"

#include <ftk/Core/FileIO.h>
#include <ftk/Core/String.h>

using namespace ftk;

namespace examples
{
    namespace objview
    {
        std::shared_ptr<ftk::TriMesh3F> read(const std::filesystem::path& path)
        {
            const auto lines = readLines(path);
            auto out = std::make_shared<ftk::TriMesh3F>();
            for (const auto& line : lines)
            {
                const auto split = ftk::split(line, { ' ', '\t' });
                const size_t size = split.size();
                if (size >= 4 && "v" == split[0])
                {
                    out->v.push_back(V3F(
                        std::atof(split[1].c_str()),
                        std::atof(split[2].c_str()),
                        std::atof(split[3].c_str())));
                }
                else if (size >= 4 && "f" == split[0])
                {
                    std::vector<Vertex3> vs;
                    for (size_t i = 1; i < size; ++i)
                    {
                        const auto split2 = ftk::split(split[i], '/');
                        Vertex3 v;
                        v.v = std::atoi(split2[0].c_str());
                        if (split2.size() > 1)
                        {
                            v.t = std::atoi(split2[1].c_str());
                        }
                        if (split2.size() > 2)
                        {
                            v.n = std::atoi(split2[2].c_str());
                        }
                        vs.push_back(v);
                    }
                    for (size_t i = 0; i < vs.size() - 1; ++i)
                    {
                        Triangle3 t;
                        t.v[0] = vs[0];
                        t.v[1] = vs[i];
                        t.v[2] = vs[i + 1];
                        out->triangles.push_back(t);
                    }
                }
            }
            return out;
        }
    }
}