// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "Document.h"

#include "ObjIO.h"

using namespace ftk;

namespace examples
{
    namespace objview
    {
        void Document::_init(
            const std::shared_ptr<Context>& context,
            const std::filesystem::path& path)
        {
            _path = path;

            _mesh = read(path);
        }

        Document::~Document()
        {}

        std::shared_ptr<Document> Document::create(
            const std::shared_ptr<Context>& context,
            const std::filesystem::path& path)
        {
            auto out = std::shared_ptr<Document>(new Document);
            out->_init(context, path);
            return out;
        }

        const std::filesystem::path& Document::getPath() const
        {
            return _path;
        }

        std::string Document::getName() const
        {
            return _path.filename().u8string();
        }

        std::string Document::getTooltip() const
        {
            return _path.u8string();
        }

        const std::shared_ptr<ftk::TriMesh3F>& Document::getMesh() const
        {
            return _mesh;
        }
    }
}