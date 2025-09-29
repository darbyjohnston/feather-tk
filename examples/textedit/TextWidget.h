// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/Ui/Label.h>
#include <ftk/Ui/ScrollWidget.h>

namespace examples
{
    namespace textedit
    {
        class Document;

        class TextWidget : public ftk::IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<Document>&,
                const std::shared_ptr<ftk::IWidget>& parent);

            TextWidget() = default;

        public:
            virtual ~TextWidget();

            static std::shared_ptr<TextWidget> create(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<Document>&,
                const std::shared_ptr<ftk::IWidget>& parent = nullptr);

            ftk::FontRole getFontRole() const;

            void setFontRole(ftk::FontRole);

            void setGeometry(const ftk::Box2I&) override;
            void sizeHintEvent(const ftk::SizeHintEvent&) override;

        private:
            std::shared_ptr<Document> _document;

            std::shared_ptr<ftk::Label> _label;
            std::shared_ptr<ftk::ScrollWidget> _scrollWidget;

            std::shared_ptr<ftk::ListObserver<std::string> > _linesObserver;
        };
    }
}