// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "DocumentModel.h"

using namespace ftk;

namespace examples
{
    namespace textedit
    {
        void DocumentModel::_init(
            const std::shared_ptr<Context>& context)
        {
            _documents = ObservableList<std::shared_ptr<Document> >::create();
            _add = ObservableValue<std::shared_ptr<Document> >::create();
            _close = ObservableValue<std::shared_ptr<Document> >::create();
            _closeAll = ObservableValue<bool>::create(false);
            _currentIndex = ObservableValue<int>::create(-1);
        }

        DocumentModel::~DocumentModel()
        {}

        std::shared_ptr<DocumentModel> DocumentModel::create(
            const std::shared_ptr<Context>& context)
        {
            auto out = std::shared_ptr<DocumentModel>(new DocumentModel);
            out->_init(context);
            return out;
        }

        const std::vector<std::shared_ptr<Document> >& DocumentModel::getList() const
        {
            return _documents->get();
        }

        std::shared_ptr<ftk::IObservableList<std::shared_ptr<Document> > > DocumentModel::observeList() const
        {
            return _documents;
        }

        void DocumentModel::add(const std::shared_ptr<Document>& document)
        {
            _documents->pushBack(document);
            _add->setAlways(document);
            _add->setAlways(nullptr);
            _currentIndex->setIfChanged(_documents->getSize() - 1);
        }

        std::shared_ptr<ftk::IObservableValue<std::shared_ptr<Document> > > DocumentModel::observeAdd() const
        {
            return _add;
        }

        void DocumentModel::close(int index)
        {
            if (index >= 0 && index < _documents->getSize())
            {
                _close->setAlways(_documents->getItem(index));
                _close->setAlways(nullptr);
                _documents->removeItem(index);

                if (index == _currentIndex->get())
                {
                    _currentIndex->setIfChanged(std::min(
                        index,
                        static_cast<int>(_documents->getSize()) - 1));
                }
                else if (index < _currentIndex->get())
                {
                    _currentIndex->setIfChanged(_currentIndex->get() - 1);
                }
            }
        }

        void DocumentModel::closeAll()
        {
            _documents->clear();
            _closeAll->setAlways(true);
            _currentIndex->setIfChanged(-1);
        }

        std::shared_ptr<ftk::IObservableValue<std::shared_ptr<Document> > > DocumentModel::observeClose() const
        {
            return _close;
        }

        std::shared_ptr<ftk::IObservableValue<bool> > DocumentModel::observeCloseAll() const
        {
            return _closeAll;
        }

        std::shared_ptr<Document> DocumentModel::getCurrent() const
        {
            const auto& docs = _documents->get();
            const int index = _currentIndex->get();
            return index >= 0 && index < docs.size() ? docs[index] : nullptr;
        }

        int DocumentModel::getCurrentIndex() const
        {
            return _currentIndex->get();
        }

        std::shared_ptr<ftk::IObservableValue<int> > DocumentModel::observeCurrentIndex() const
        {
            return _currentIndex;
        }

        void DocumentModel::setCurrentIndex(int value)
        {
            _currentIndex->setIfChanged(value);
        }
    }
}