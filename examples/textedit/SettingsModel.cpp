// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "SettingsModel.h"

using namespace ftk;

namespace examples
{
    namespace textedit
    {
        bool WindowOptions::operator == (const WindowOptions& other) const
        {
            return
                settings == other.settings &&
                split == other.split;
        }

        bool WindowOptions::operator != (const WindowOptions& other) const
        {
            return !(*this == other);
        }

        void SettingsModel::_init(
            const std::shared_ptr<Context>& context)
        {
            _windowOptions = ObservableValue<WindowOptions>::create();
            _textEditOptions = ObservableValue<TextEditOptions>::create();
        }

        SettingsModel::~SettingsModel()
        {}

        std::shared_ptr<SettingsModel> SettingsModel::create(
            const std::shared_ptr<Context>& context)
        {
            auto out = std::shared_ptr<SettingsModel>(new SettingsModel);
            out->_init(context);
            return out;
        }

        const WindowOptions& SettingsModel::getWindowOptions() const
        {
            return _windowOptions->get();
        }

        std::shared_ptr<IObservableValue<WindowOptions> > SettingsModel::observeWindowOptions() const
        {
            return _windowOptions;
        }

        void SettingsModel::setWindowOptions(const WindowOptions& value)
        {
            _windowOptions->setIfChanged(value);
        }

        const ftk::TextEditOptions& SettingsModel::getTextEditOptions() const
        {
            return _textEditOptions->get();
        }

        std::shared_ptr<IObservableValue<ftk::TextEditOptions> > SettingsModel::observeTextEditOptions() const
        {
            return _textEditOptions;
        }

        void SettingsModel::setTextEditOptions(const ftk::TextEditOptions& value)
        {
            _textEditOptions->setIfChanged(value);
        }
    }
}