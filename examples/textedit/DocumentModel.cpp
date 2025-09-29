// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "DocumentModel.h"

#include <ftk/Core/FileIO.h>

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

            _remove = ObservableValue<int>::create(-1);

            _clear = ObservableValue<bool>::create(false);

            _current = ObservableValue<int>::create(-1);

            _fontRole = ObservableValue<FontRole>::create(FontRole::Mono);
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
            _current->setIfChanged(_documents->getSize() - 1);
        }

        std::shared_ptr<ftk::IObservableValue<std::shared_ptr<Document> > > DocumentModel::observeAdd() const
        {
            return _add;
        }

        void DocumentModel::remove(int index)
        {
            if (index >= 0 && index < _documents->getSize())
            {
                _documents->removeItem(index);
                _remove->setAlways(index);

                if (index == _current->get())
                {
                    _current->setIfChanged(std::min(
                        index,
                        static_cast<int>(_documents->getSize()) - 1));
                }
                else if (index < _current->get())
                {
                    _current->setIfChanged(_current->get() - 1);
                }
            }
        }

        std::shared_ptr<ftk::IObservableValue<int> > DocumentModel::observeRemove() const
        {
            return _remove;
        }

        void DocumentModel::clear()
        {
            _documents->clear();
            _clear->setAlways(true);
            _current->setIfChanged(-1);
        }

        std::shared_ptr<ftk::IObservableValue<bool> > DocumentModel::observeClear() const
        {
            return _clear;
        }

        int DocumentModel::getCurrent() const
        {
            return _current->get();
        }

        std::shared_ptr<ftk::IObservableValue<int> > DocumentModel::observeCurrent() const
        {
            return _current;
        }

        void DocumentModel::setCurrent(int value)
        {
            _current->setIfChanged(value);
        }

        ftk::FontRole DocumentModel::getFontRole() const
        {
            return _fontRole->get();
        }

        std::shared_ptr<IObservableValue<FontRole> > DocumentModel::observeFontRole() const
        {
            return _fontRole;
        }

        void DocumentModel::setFontRole(FontRole value)
        {
            _fontRole->setIfChanged(value);
        }
    }
}