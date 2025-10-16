// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include "Document.h"

#include <ftk/UI/Settings.h>
#include <ftk/UI/TextEdit.h>

namespace examples
{
    namespace textedit
    {
        struct WindowOptions
        {
            bool  settings = false;
            float split    = .7F;

            bool operator == (const WindowOptions&) const;
            bool operator != (const WindowOptions&) const;
        };

        class SettingsModel : public std::enable_shared_from_this<SettingsModel>
        {
        protected:
            void _init(const std::shared_ptr<ftk::Context>&);

            SettingsModel() = default;

        public:
            virtual ~SettingsModel();

            static std::shared_ptr<SettingsModel> create(
                const std::shared_ptr<ftk::Context>&);

            const std::vector<std::filesystem::path>& getRecentFiles() const;
            void setRecentFiles(const std::vector<std::filesystem::path>&);

            const WindowOptions& getWindowOptions() const;
            std::shared_ptr<ftk::IObservableValue<WindowOptions> > observeWindowOptions() const;
            void setWindowOptions(const WindowOptions&);

            const ftk::TextEditOptions& getTextEditOptions() const;
            std::shared_ptr<ftk::IObservableValue<ftk::TextEditOptions> > observeTextEditOptions() const;
            void setTextEditOptions(const ftk::TextEditOptions&);

            const ftk::TextEditModelOptions& getTextEditModelOptions() const;
            std::shared_ptr<ftk::IObservableValue<ftk::TextEditModelOptions> > observeTextEditModelOptions() const;
            void setTextEditModelOptions(const ftk::TextEditModelOptions&);

        private:
            std::shared_ptr<ftk::Settings> _settings;
            std::vector<std::filesystem::path> _recentFiles;
            std::shared_ptr<ftk::ObservableValue<WindowOptions> > _windowOptions;
            std::shared_ptr<ftk::ObservableValue<ftk::TextEditOptions> > _textEditOptions;
            std::shared_ptr<ftk::ObservableValue<ftk::TextEditModelOptions> > _textEditModelOptions;
        };

        void to_json(nlohmann::json&, const WindowOptions&);

        void from_json(const nlohmann::json&, WindowOptions&);
    }
}