// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/TabWidget.h>

namespace examples
{
    namespace imageview
    {
        class App;
        class Document;
        class ImageView;

        //! Document tabs widget.
        class DocumentTabs : public ftk::IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<App>&,
                const std::shared_ptr<ftk::IWidget>& parent);

            DocumentTabs() = default;

        public:
            virtual ~DocumentTabs();

            //! Create a new widget.
            static std::shared_ptr<DocumentTabs> create(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<App>&,
                const std::shared_ptr<ftk::IWidget>& parent = nullptr);

            void setGeometry(const ftk::Box2I&) override;
            void sizeHintEvent(const ftk::SizeHintEvent&) override;

        private:
            std::shared_ptr<ftk::TabWidget> _tabWidget;
            std::map<std::shared_ptr<Document>, std::shared_ptr<ftk::IWidget> > _views;

            std::shared_ptr<ftk::ValueObserver<std::weak_ptr<Document> > > _addObserver;
            std::shared_ptr<ftk::ValueObserver<std::weak_ptr<Document> > > _closeObserver;
            std::shared_ptr<ftk::ValueObserver<bool> > _clearObserver;
            std::shared_ptr<ftk::ValueObserver<int> > _currentObserver;
        };
    }
}