// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "Document.h"

#include <ftk/Core/FileIO.h>

using namespace ftk;

namespace examples
{
    namespace textedit
    {
        void Document::_init(
            const std::shared_ptr<Context>& context,
            const std::filesystem::path& path)
        {
            _path = path;

            _model = ftk::TextEditModel::create();
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

        const std::shared_ptr<ftk::TextEditModel>& Document::getModel() const
        {
            return _model;
        }
    }
}