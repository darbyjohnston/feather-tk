// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <ftk/Core/ObservableList.h>
#include <ftk/Core/ObservableValue.h>

namespace ftk
{
    class Context;

    //! Base class for documents.
    class IDocument : public std::enable_shared_from_this<IDocument>
    {
    public:
        virtual ~IDocument() = 0;
    };

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

        const std::vector<std::shared_ptr<IDocument> >& getList() const;
        std::shared_ptr<ftk::IObservableList<std::shared_ptr<IDocument> > > observeList() const;

        ///@}

        //! \name Add Documents
        ///@{

        void add(const std::shared_ptr<IDocument>&);
        std::shared_ptr<ftk::IObservableValue<std::weak_ptr<IDocument> > > observeAdd() const;

        ///@}

        //! \name Close Documents
        ///@{

        void close(int);
        void closeAll();
        std::shared_ptr<ftk::IObservableValue<std::weak_ptr<IDocument> > > observeClose() const;
        std::shared_ptr<ftk::IObservableValue<bool> > observeCloseAll() const;

        ///@}

        //! \name Current Document
        ///@{

        std::shared_ptr<IDocument> getCurrent() const;
        int getCurrentIndex() const;
        std::shared_ptr<ftk::IObservableValue<std::shared_ptr<IDocument> > > observeCurrent() const;
        std::shared_ptr<ftk::IObservableValue<int> > observeCurrentIndex() const;
        void setCurrentIndex(int);

        ///@}

    private:
        std::shared_ptr<ftk::ObservableList<std::shared_ptr<IDocument> > > _documents;
        std::shared_ptr<ftk::ObservableValue<std::weak_ptr<IDocument> > > _add;
        std::shared_ptr<ftk::ObservableValue<std::weak_ptr<IDocument> > > _close;
        std::shared_ptr<ftk::ObservableValue<bool> > _closeAll;
        std::shared_ptr<ftk::ObservableValue<std::shared_ptr<IDocument> > > _current;
        std::shared_ptr<ftk::ObservableValue<int> > _currentIndex;
    };
}