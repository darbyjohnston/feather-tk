// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/Core/Context.h>
#include <ftk/Core/Image.h>

#include <filesystem>

namespace examples
{
    namespace imageview
    {
        //! Document.
        class Document : public std::enable_shared_from_this<Document>
        {
        protected:
            void _init(
                const std::shared_ptr<ftk::Context>&,
                const std::filesystem::path& = std::filesystem::path());

            Document() = default;

        public:
            virtual ~Document();

            //! Create a new document.
            static std::shared_ptr<Document> create(
                const std::shared_ptr<ftk::Context>&,
                const std::filesystem::path& = std::filesystem::path());

            //! \name Information
            ///@{

            const std::filesystem::path& getPath() const;
            std::string getName() const;
            std::string getTooltip() const;

            ///@}

            //! \name Image
            ///@{

            const std::shared_ptr<ftk::Image>& getImage() const;

            ///@}

        private:
            std::filesystem::path _path;
            std::shared_ptr<ftk::Image> _image;
        };
    }
}
