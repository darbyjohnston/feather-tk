// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/gl/Render.h>

#include <feather-tk/gl/GL.h>
#include <feather-tk/gl/Mesh.h>
#include <feather-tk/gl/Shader.h>
#include <feather-tk/gl/TextureAtlas.h>

#include <chrono>
#include <list>
#include <map>

namespace feather_tk
{
    namespace gl
    {
        std::string vertexSource();
        std::string meshFragmentSource();
        std::string colorMeshVertexSource();
        std::string colorMeshFragmentSource();
        std::string textureFragmentSource();
        std::string textFragmentSource();
        std::string imageFragmentSource();

        struct Render::Private
        {
            std::weak_ptr<LogSystem> logSystem;

            Size2I size;
            RenderOptions options;
            Box2I viewport;
            bool clipRectEnabled = false;
            Box2I clipRect;
            M44F transform;
            
            std::map<std::string, std::shared_ptr<gl::Shader> > shaders;
            std::shared_ptr<TextureCache> textureCache;
            std::shared_ptr<gl::TextureAtlas> glyphAtlas;
            std::map<GlyphInfo, BoxPackID> glyphIDs;
            TriMesh2F textMesh;
            std::map<std::string, std::shared_ptr<gl::VBO> > vbos;
            std::map<std::string, std::shared_ptr<gl::VAO> > vaos;

            std::chrono::time_point<std::chrono::steady_clock> startTime;
            struct Stats
            {
                int renderTime = 0;
                size_t triCount = 0;
                size_t textureCount = 0;
                size_t glyphCount = 0;
            };
            Stats stats;
            std::list<Stats> statsList;
            size_t statsCounter = 0;
        };
    }
}

