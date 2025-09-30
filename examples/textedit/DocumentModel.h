// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include "Document.h"

#include <ftk/UI/Style.h>

namespace examples
{
    namespace textedit
    {
        class DocumentModel : public std::enable_shared_from_this<DocumentModel>
        {
        protected:
            void _init(const std::shared_ptr<ftk::Context>&);

            DocumentModel() = default;

        public:
            virtual ~DocumentModel();

            static std::shared_ptr<DocumentModel> create(
                const std::shared_ptr<ftk::Context>&);

            const std::vector<std::shared_ptr<Document> >& getList() const;

            std::shared_ptr<ftk::IObservableList<std::shared_ptr<Document> > > observeList() const;

            void add(const std::shared_ptr<Document>&);

            std::shared_ptr<ftk::IObservableValue<std::shared_ptr<Document> > > observeAdd() const;

            void remove(int);

            std::shared_ptr<ftk::IObservableValue<int> > observeRemove() const;

            void clear();

            std::shared_ptr<ftk::IObservableValue<bool> > observeClear() const;

            int getCurrent() const;

            std::shared_ptr<ftk::IObservableValue<int> > observeCurrent() const;

            void setCurrent(int);

            ftk::FontRole getFontRole() const;

            std::shared_ptr<ftk::IObservableValue<ftk::FontRole> > observeFontRole() const;

            void setFontRole(ftk::FontRole);

        private:
            std::shared_ptr<ftk::ObservableList<std::shared_ptr<Document> > > _documents;
            std::shared_ptr<ftk::ObservableValue<std::shared_ptr<Document> > > _add;
            std::shared_ptr<ftk::ObservableValue<int> > _remove;
            std::shared_ptr<ftk::ObservableValue<bool> > _clear;
            std::shared_ptr<ftk::ObservableValue<int> > _current;
            std::shared_ptr<ftk::ObservableValue<ftk::FontRole> > _fontRole;
        };
    }
}