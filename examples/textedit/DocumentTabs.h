// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/Label.h>
#include <ftk/UI/RowLayout.h>
#include <ftk/UI/TabWidget.h>
#include <ftk/UI/TextEdit.h>

namespace examples
{
    namespace textedit
    {
        class App;
        class Document;

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

            static std::shared_ptr<DocumentTabs> create(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<App>&,
                const std::shared_ptr<ftk::IWidget>& parent = nullptr);

            void setGeometry(const ftk::Box2I&) override;
            void sizeHintEvent(const ftk::SizeHintEvent&) override;

        private:
            std::shared_ptr<ftk::TabWidget> _tabWidget;
            std::map<std::shared_ptr<Document>, std::shared_ptr<ftk::TextEdit> > _textEdits;

            std::shared_ptr<ftk::ValueObserver<std::shared_ptr<Document> > > _addDocumentObserver;
            std::shared_ptr<ftk::ValueObserver<std::shared_ptr<Document> > > _removeDocumentObserver;
            std::shared_ptr<ftk::ValueObserver<bool> > _clearDocumentsObserver;
            std::shared_ptr<ftk::ValueObserver<int> > _currentDocumentObserver;
            std::map<std::shared_ptr<Document>, std::shared_ptr<ftk::ValueObserver<std::filesystem::path> > > _documentPathObservers;
            std::shared_ptr<ftk::ValueObserver<ftk::TextEditOptions> > _textEditOptionsObserver;
            std::shared_ptr<ftk::ValueObserver<ftk::TextEditModelOptions> > _textEditModelOptionsObserver;
        };
    }
}