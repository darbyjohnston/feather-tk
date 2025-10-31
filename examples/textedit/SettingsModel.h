// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include "Settings.h"

#include <ftk/UI/FileBrowser.h>
#include <ftk/UI/Settings.h>
#include <ftk/UI/TextEdit.h>

namespace textedit
{
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

        //! \name Text Edit Options
        ///@{

        const ftk::TextEditOptions& getTextEditOptions() const;
        std::shared_ptr<ftk::IObservableValue<ftk::TextEditOptions> > observeTextEditOptions() const;
        void setTextEditOptions(const ftk::TextEditOptions&);

        const ftk::TextEditModelOptions& getTextEditModelOptions() const;
        std::shared_ptr<ftk::IObservableValue<ftk::TextEditModelOptions> > observeTextEditModelOptions() const;
        void setTextEditModelOptions(const ftk::TextEditModelOptions&);

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
        std::shared_ptr<ftk::FileBrowserSystem> _fileBrowserSystem;
        std::shared_ptr<ftk::ObservableValue<ftk::TextEditOptions> > _textEditOptions;
        std::shared_ptr<ftk::ObservableValue<ftk::TextEditModelOptions> > _textEditModelOptions;
        std::shared_ptr<ftk::ObservableValue<WindowSettings> > _window;
        std::shared_ptr<ftk::ObservableValue<StyleSettings> > _style;
    };
}
