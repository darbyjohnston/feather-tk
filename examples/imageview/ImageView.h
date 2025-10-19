// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/IWidget.h>

#include <ftk/Core/Image.h>

namespace examples
{
    namespace imageview
    {
        class Document;

        //! Image view widget.
        class ImageView : public ftk::IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<Document>&,
                const std::shared_ptr<ftk::IWidget>& parent);

            ImageView() = default;

        public:
            virtual ~ImageView();

            //! Create a new view.
            static std::shared_ptr<ImageView> create(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<Document>&,
                const std::shared_ptr<ftk::IWidget>& parent = nullptr);

            void sizeHintEvent(const ftk::SizeHintEvent&) override;
            void drawEvent(const ftk::Box2I&, const ftk::DrawEvent&) override;

        private:
            std::shared_ptr<ftk::Image> _image;
        };
    }
}