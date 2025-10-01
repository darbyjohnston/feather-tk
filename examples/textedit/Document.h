// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/TextEditModel.h>

#include <filesystem>

namespace examples
{
    namespace textedit
    {
        class Document : public std::enable_shared_from_this<Document>
        {
        protected:
            void _init(
                const std::shared_ptr<ftk::Context>&,
                const std::filesystem::path& = std::filesystem::path());

            Document() = default;

        public:
            virtual ~Document();

            static std::shared_ptr<Document> create(
                const std::shared_ptr<ftk::Context>&,
                const std::filesystem::path& = std::filesystem::path());

            const std::filesystem::path& getPath() const;

            std::string getName() const;

            const std::shared_ptr<ftk::TextEditModel>& getModel() const;

        private:
            std::filesystem::path _path;
            std::shared_ptr<ftk::TextEditModel> _model;
        };
    }
}
