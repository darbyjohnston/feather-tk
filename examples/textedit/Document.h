// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/Context.h>
#include <feather-tk/core/ObservableList.h>

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

            const std::vector<std::string>& getLines() const;

            std::shared_ptr<ftk::IObservableList<std::string> > observeLines() const;

            void setLines(const std::vector<std::string>&);

        private:
            std::filesystem::path _path;
            std::shared_ptr<ftk::ObservableList<std::string> > _lines;
        };
    }
}
