// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include "Document.h"

#include <ftk/UI/App.h>
#include <ftk/UI/Settings.h>

namespace examples
{
    namespace objview
    {
        //! Window settings.
        struct WindowSettings
        {
            bool  settings = false;
            float split    = .7F;

            bool operator == (const WindowSettings&) const;
            bool operator != (const WindowSettings&) const;
        };

        //! Style settings.
        struct StyleSettings
        {
            float displayScale = 2.F;
            ftk::ColorStyle colorStyle = ftk::ColorStyle::Dark;

            bool operator == (const StyleSettings&) const;
            bool operator != (const StyleSettings&) const;
        };

        //! Global settings that are save to file.
        class SettingsModel : public std::enable_shared_from_this<SettingsModel>
        {
        protected:
            void _init(
                const std::shared_ptr<ftk::Context>&,
                float defaultDisplayScale);

            SettingsModel() = default;

        public:
            virtual ~SettingsModel();

            //! Create a new settings model.
            static std::shared_ptr<SettingsModel> create(
                const std::shared_ptr<ftk::Context>&,
                float defaultDisplayScale);

            //! \name Recent Files
            ///@{

            const std::vector<std::filesystem::path>& getRecentFiles() const;
            void setRecentFiles(const std::vector<std::filesystem::path>&);

            ///@}

            //! \name Window
            ///@{

            const WindowSettings& getWindow() const;
            std::shared_ptr<ftk::IObservableValue<WindowSettings> > observeWindow() const;
            void setWindow(const WindowSettings&);

            ///@}

            //! \name Style
            ///@{

            const StyleSettings& getStyle() const;
            std::shared_ptr<ftk::IObservableValue<StyleSettings> > observeStyle() const;
            void setStyle(const StyleSettings&);

            ///@}

        private:
            std::shared_ptr<ftk::Settings> _settings;
            std::vector<std::filesystem::path> _recentFiles;
            std::shared_ptr<ftk::ObservableValue<WindowSettings> > _window;
            std::shared_ptr<ftk::ObservableValue<StyleSettings> > _style;
        };

        void to_json(nlohmann::json&, const WindowSettings&);
        void to_json(nlohmann::json&, const StyleSettings&);

        void from_json(const nlohmann::json&, WindowSettings&);
        void from_json(const nlohmann::json&, StyleSettings&);
    }
}