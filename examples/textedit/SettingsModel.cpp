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
            _settings = Settings::create(context, getSettingsPath("feather-tk", "textedit.json"));

            nlohmann::json recentFiles;
            _settings->get("/RecentFiles", recentFiles);
            if (recentFiles.is_array())
            {
                for (const auto& i : recentFiles)
                {
                    if (i.is_string())
                    {
                        _recentFiles.push_back(i.get<std::string>());
                    }
                }
            }

            WindowOptions windowOptions;
            _settings->getT("/WindowOptions", windowOptions);
            _windowOptions = ObservableValue<WindowOptions>::create(windowOptions);

            TextEditOptions textEditOptions;
            _settings->getT("/TextEditOptions", textEditOptions);
            _textEditOptions = ObservableValue<TextEditOptions>::create(textEditOptions);

            TextEditModelOptions textEditModelOptions;
            _settings->getT("/TextEditModelOptions", textEditModelOptions);
            _textEditModelOptions = ObservableValue<TextEditModelOptions>::create(textEditModelOptions);
        }

        SettingsModel::~SettingsModel()
        {
            nlohmann::json recentFiles;
            for (const auto& i : _recentFiles)
            {
                recentFiles.push_back(i);
            }
            _settings->set("/RecentFiles", recentFiles);
            _settings->setT("/WindowOptions", _windowOptions->get());
            _settings->setT("/TextEditOptions", _textEditOptions->get());
            _settings->setT("/TextEditModelOptions", _textEditModelOptions->get());
        }

        std::shared_ptr<SettingsModel> SettingsModel::create(
            const std::shared_ptr<Context>& context)
        {
            auto out = std::shared_ptr<SettingsModel>(new SettingsModel);
            out->_init(context);
            return out;
        }

        const std::vector<std::filesystem::path>& SettingsModel::getRecentFiles() const
        {
            return _recentFiles;
        }

        void SettingsModel::setRecentFiles(const std::vector<std::filesystem::path>& value)
        {
            _recentFiles = value;
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

        const TextEditOptions& SettingsModel::getTextEditOptions() const
        {
            return _textEditOptions->get();
        }

        std::shared_ptr<IObservableValue<TextEditOptions> > SettingsModel::observeTextEditOptions() const
        {
            return _textEditOptions;
        }

        void SettingsModel::setTextEditOptions(const TextEditOptions& value)
        {
            _textEditOptions->setIfChanged(value);
        }

        const TextEditModelOptions& SettingsModel::getTextEditModelOptions() const
        {
            return _textEditModelOptions->get();
        }

        std::shared_ptr<IObservableValue<TextEditModelOptions> > SettingsModel::observeTextEditModelOptions() const
        {
            return _textEditModelOptions;
        }

        void SettingsModel::setTextEditModelOptions(const TextEditModelOptions& value)
        {
            _textEditModelOptions->setIfChanged(value);
        }

        void to_json(nlohmann::json& json, const WindowOptions& value)
        {
            json["Settings"] = value.settings;
            json["Split"] = value.split;
        }

        void from_json(const nlohmann::json& json, WindowOptions& value)
        {
            json.at("Settings").get_to(value.settings);
            json.at("Split").get_to(value.split);
        }
    }
}