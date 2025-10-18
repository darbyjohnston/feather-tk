// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include "Document.h"

#include <ftk/Core/ObservableValue.h>

namespace examples
{
    namespace imageview
    {
        //! Document model.
        class DocumentModel : public std::enable_shared_from_this<DocumentModel>
        {
        protected:
            void _init(const std::shared_ptr<ftk::Context>&);

            DocumentModel() = default;

        public:
            virtual ~DocumentModel();

            //! Create a new document model.
            static std::shared_ptr<DocumentModel> create(
                const std::shared_ptr<ftk::Context>&);

            //! \name Documents
            ///@{

            const std::vector<std::shared_ptr<Document> >& getList() const;
            std::shared_ptr<ftk::IObservableList<std::shared_ptr<Document> > > observeList() const;

            ///@}

            //! \name Add Documents
            ///@{

            void add(const std::shared_ptr<Document>&);
            std::shared_ptr<ftk::IObservableValue<std::weak_ptr<Document> > > observeAdd() const;

            ///@}

            //! \name Close Documents
            ///@{

            void close(int);
            void closeAll();
            std::shared_ptr<ftk::IObservableValue<std::weak_ptr<Document> > > observeClose() const;
            std::shared_ptr<ftk::IObservableValue<bool> > observeCloseAll() const;

            ///@}

            //! \name Current Document
            ///@{

            std::shared_ptr<Document> getCurrent() const;
            int getCurrentIndex() const;
            std::shared_ptr<ftk::IObservableValue<std::shared_ptr<Document> > > observeCurrent() const;
            std::shared_ptr<ftk::IObservableValue<int> > observeCurrentIndex() const;
            void setCurrentIndex(int);

            ///@}

        private:
            std::shared_ptr<ftk::ObservableList<std::shared_ptr<Document> > > _documents;
            std::shared_ptr<ftk::ObservableValue<std::weak_ptr<Document> > > _add;
            std::shared_ptr<ftk::ObservableValue<std::weak_ptr<Document> > > _close;
            std::shared_ptr<ftk::ObservableValue<bool> > _closeAll;
            std::shared_ptr<ftk::ObservableValue<std::shared_ptr<Document> > > _current;
            std::shared_ptr<ftk::ObservableValue<int> > _currentIndex;
        };
    }
}