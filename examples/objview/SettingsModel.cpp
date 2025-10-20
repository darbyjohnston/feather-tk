// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "SettingsModel.h"

using namespace ftk;

namespace examples
{
    namespace objview
    {
        void SettingsModel::_init(
            const std::shared_ptr<Context>& context,
            float defaultDisplayScale)
        {
            _settings = Settings::create(context, getSettingsPath("feather-tk", "objview.json"));

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

            WindowSettings window;
            _settings->getT("/Window", window);
            _window = ObservableValue<WindowSettings>::create(window);

            RenderSettings render;
            _settings->getT("/Render", render);
            _render = ObservableValue<RenderSettings>::create(render);

            AnimSettings anim;
            _settings->getT("/Anim", anim);
            _anim = ObservableValue<AnimSettings>::create(anim);

            StyleSettings style;
            style.displayScale = defaultDisplayScale;
            _settings->getT("/Style", style);
            _style = ObservableValue<StyleSettings>::create(style);
        }

        SettingsModel::~SettingsModel()
        {
            nlohmann::json recentFiles;
            for (const auto& i : _recentFiles)
            {
                recentFiles.push_back(i);
            }
            _settings->set("/RecentFiles", recentFiles);
            _settings->setT("/Window", _window->get());
            _settings->setT("/Render", _render->get());
            _settings->setT("/Anim", _anim->get());
            _settings->setT("/Style", _style->get());
        }

        std::shared_ptr<SettingsModel> SettingsModel::create(
            const std::shared_ptr<Context>& context,
            float defaultDisplayScale)
        {
            auto out = std::shared_ptr<SettingsModel>(new SettingsModel);
            out->_init(context, defaultDisplayScale);
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

        const WindowSettings& SettingsModel::getWindow() const
        {
            return _window->get();
        }

        std::shared_ptr<IObservableValue<WindowSettings> > SettingsModel::observeWindow() const
        {
            return _window;
        }

        void SettingsModel::setWindow(const WindowSettings& value)
        {
            _window->setIfChanged(value);
        }

        const RenderSettings& SettingsModel::getRender() const
        {
            return _render->get();
        }

        std::shared_ptr<IObservableValue<RenderSettings> > SettingsModel::observeRender() const
        {
            return _render;
        }

        void SettingsModel::setRender(const RenderSettings& value)
        {
            _render->setIfChanged(value);
        }

        const AnimSettings& SettingsModel::getAnim() const
        {
            return _anim->get();
        }

        std::shared_ptr<IObservableValue<AnimSettings> > SettingsModel::observeAnim() const
        {
            return _anim;
        }

        void SettingsModel::setAnim(const AnimSettings& value)
        {
            _anim->setIfChanged(value);
        }

        const StyleSettings& SettingsModel::getStyle() const
        {
            return _style->get();
        }

        std::shared_ptr<IObservableValue<StyleSettings> > SettingsModel::observeStyle() const
        {
            return _style;
        }

        void SettingsModel::setStyle(const StyleSettings& value)
        {
            _style->setIfChanged(value);
        }
    }
}
