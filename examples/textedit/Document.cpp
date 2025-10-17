// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "Document.h"

#include <ftk/Core/FileIO.h>

using namespace ftk;

namespace examples
{
    namespace textedit
    {
        void Document::_init(
            const std::shared_ptr<Context>& context,
            const std::filesystem::path& path)
        {
            _path = ObservableValue<std::filesystem::path>::create(path);
            _name = ObservableValue<std::string>::create();
            _tooltip = ObservableValue<std::string>::create();

            std::vector<std::string> lines;
            if (!path.empty())
            {
                lines = readLines(path);
            }
            _model = TextEditModel::create(context, lines);

            _changed = ObservableValue<bool>::create(false);

            _nameUpdate();

            _textObserver = ListObserver<std::string>::create(
                _model->observeText(),
                [this](const std::vector<std::string>&)
                {
                    if (_changed->setIfChanged(true))
                    {
                        _nameUpdate();
                    }
                },
                ObserverAction::Suppress);
        }

        Document::~Document()
        {}

        std::shared_ptr<Document> Document::create(
            const std::shared_ptr<Context>& context,
            const std::filesystem::path& path)
        {
            auto out = std::shared_ptr<Document>(new Document);
            out->_init(context, path);
            return out;
        }

        const std::filesystem::path& Document::getPath() const
        {
            return _path->get();
        }

        std::shared_ptr<ftk::IObservableValue<std::filesystem::path> > Document::observePath() const
        {
            return _path;
        }

        std::shared_ptr<ftk::IObservableValue<std::string> > Document::observeName() const
        {
            return _name;
        }

        std::shared_ptr<ftk::IObservableValue<std::string> > Document::observeTooltip() const
        {
            return _tooltip;
        }

        const std::shared_ptr<ftk::TextEditModel>& Document::getModel() const
        {
            return _model;
        }

        bool Document::isChanged() const
        {
            return _changed->get();
        }

        std::shared_ptr<ftk::IObservableValue<bool> > Document::observeChanged() const
        {
            return _changed;
        }

        void Document::resetChanged()
        {
            _changed->setIfChanged(false);
        }

        void Document::save()
        {
            writeLines(_path->get(), _model->getText());
            _changed->setIfChanged(false);
            _nameUpdate();
        }

        void Document::saveAs(const std::filesystem::path& path)
        {
            writeLines(path, _model->getText());
            _path->setIfChanged(path);
            _changed->setIfChanged(false);
            _nameUpdate();
        }

        void Document::_nameUpdate()
        {
            const std::filesystem::path& path = _path->get();
            std::string name = !path.empty() ? path.filename().u8string() : "Untitled";
            if (_changed->get())
            {
                name += "*";
            }
            _name->setIfChanged(name);
            _tooltip->setIfChanged(!path.empty() ? path.u8string() : "Untitled");
        }
    }
}