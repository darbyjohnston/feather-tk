// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/Settings.h>

#include <feather-tk/core/Context.h>
#include <feather-tk/core/File.h>
#include <feather-tk/core/FileIO.h>
#include <feather-tk/core/Format.h>
#include <feather-tk/core/LogSystem.h>
#include <feather-tk/core/String.h>

#include <map>

namespace feather_tk
{
    std::filesystem::path getSettingsPath(
        const std::string& directory,
        const std::string& fileName)
    {
        return getUserPath(UserPath::Documents) / directory / fileName;
    }

    struct Settings::Private
    {
        std::weak_ptr<LogSystem> logSystem;
        std::filesystem::path path;
        nlohmann::json settings;
    };

    Settings::Settings(
        const std::shared_ptr<Context>& context,
        const std::filesystem::path& path,
        bool reset) :
        _p(new Private)
    {
        FEATHER_TK_P();

        auto logSystem = context->getLogSystem();
        p.logSystem = logSystem;

        p.path = path;

        if (!p.path.empty())
        {
            if (p.path.has_parent_path())
            {
                std::filesystem::create_directories(p.path.parent_path());
            }
            if (std::filesystem::exists(p.path) && !reset)
            {
                const std::string contents = read(FileIO::create(p.path, FileMode::Read));
                try
                {
                    p.settings = nlohmann::json::parse(contents);
                }
                catch (const std::exception& e)
                {
                    logSystem->print(
                        "feather_tk::Settings",
                        Format("Cannot read settings: {0}: {1}").arg(p.path).arg(e.what()),
                        LogType::Error);
                }
            }
        }
    }

    Settings::~Settings()
    {
        save();
    }

    std::shared_ptr<Settings> Settings::create(
        const std::shared_ptr<Context>& context,
        const std::filesystem::path& path,
        bool reset)
    {
        return std::shared_ptr<Settings>(new Settings(context, path, reset));
    }

    const std::filesystem::path& Settings::getPath() const
    {
        return _p->path;
    }

    void Settings::save()
    {
        FEATHER_TK_P();
        if (!p.path.empty())
        {
            try
            {
                FileIO::create(p.path, FileMode::Write)->write(p.settings.dump(4));
            }
            catch (const std::exception& e)
            {
                if (auto logSystem = p.logSystem.lock())
                {
                    logSystem->print(
                        "feather_tk::Settings",
                        Format("Cannot write settings: {0}: {1}").arg(p.path).arg(e.what()),
                        LogType::Error);
                }
            }
        }
    }

    bool Settings::contains(const std::string& key) const
    {
        FEATHER_TK_P();
        return p.settings.contains(nlohmann::json::json_pointer(key));
    }

    bool Settings::get(const std::string& key, nlohmann::json& value) const
    {
        FEATHER_TK_P();
        bool out = false;
        try
        {
            value = p.settings.at(nlohmann::json::json_pointer(key));
            out = true;
        }
        catch (const std::exception&)
        {}
        return out;
    }

    bool Settings::get(const std::string& key, bool& value)
    {
        FEATHER_TK_P();
        bool out = false;
        try
        {
            auto i = p.settings.at(nlohmann::json::json_pointer(key));
            if (i.is_boolean())
            {
                value = i;
                out = true;
            }
        }
        catch (const std::exception&)
        {}
        return out;
    }

    bool Settings::get(const std::string& key, int& value)
    {
        FEATHER_TK_P();
        bool out = false;
        try
        {
            auto i = p.settings.at(nlohmann::json::json_pointer(key));
            if (i.is_number_integer())
            {
                value = i;
                out = true;
            }
        }
        catch (const std::exception&)
        {}
        return out;
    }

    bool Settings::get(const std::string& key, int64_t& value)
    {
        bool out = false;
        FEATHER_TK_P();
        try
        {
            auto i = p.settings.at(nlohmann::json::json_pointer(key));
            if (i.is_number_integer())
            {
                value = i;
                out = true;
            }
        }
        catch (const std::exception&)
        {}
        return out;
    }

    bool Settings::get(const std::string& key, float& value)
    {
        FEATHER_TK_P();
        bool out = false;
        try
        {
            auto i = p.settings.at(nlohmann::json::json_pointer(key));
            if (i.is_number_float())
            {
                value = i;
                out = true;
            }
        }
        catch (const std::exception&)
        {}
        return out;
    }

    bool Settings::get(const std::string& key, double& value)
    {
        FEATHER_TK_P();
        bool out = false;
        try
        {
            auto i = p.settings.at(nlohmann::json::json_pointer(key));
            if (i.is_number_float())
            {
                value = i;
                out = true;
            }
        }
        catch (const std::exception&)
        {}
        return out;
    }

    bool Settings::get(const std::string& key, size_t& value)
    {
        FEATHER_TK_P();
        bool out = false;
        try
        {
            auto i = p.settings.at(nlohmann::json::json_pointer(key));
            if (i.is_number_unsigned())
            {
                value = i;
                out = true;
            }
        }
        catch (const std::exception&)
        {}
        return out;
    }

    bool Settings::get(const std::string& key, std::string& value)
    {
        FEATHER_TK_P();
        bool out = false;
        try
        {
            auto i = p.settings.at(nlohmann::json::json_pointer(key));
            if (i.is_string())
            {
                value = i;
                out = true;
            }
        }
        catch (const std::exception&)
        {}
        return out;
    }

    void Settings::set(const std::string& key, const nlohmann::json& value)
    {
        try
        {
            _p->settings[nlohmann::json::json_pointer(key)] = value;
        }
        catch (const std::exception&)
        {}
    }

    void Settings::set(const std::string& key, bool value)
    {
        try
        {
            _p->settings[nlohmann::json::json_pointer(key)] = value;
        }
        catch (const std::exception&)
        {}
    }

    void Settings::set(const std::string& key, int value)
    {
        try
        {
            _p->settings[nlohmann::json::json_pointer(key)] = value;
        }
        catch (const std::exception&)
        {}
    }

    void Settings::set(const std::string& key, int64_t value)
    {
        try
        {
            _p->settings[nlohmann::json::json_pointer(key)] = value;
        }
        catch (const std::exception&)
        {}
    }

    void Settings::set(const std::string& key, float value)
    {
        try
        {
            _p->settings[nlohmann::json::json_pointer(key)] = value;
        }
        catch (const std::exception&)
        {}
    }

    void Settings::set(const std::string& key, double value)
    {
        try
        {
            _p->settings[nlohmann::json::json_pointer(key)] = value;
        }
        catch (const std::exception&)
        {}
    }

    void Settings::set(const std::string& key, size_t value)
    {
        try
        {
            _p->settings[nlohmann::json::json_pointer(key)] = value;
        }
        catch (const std::exception&)
        {}
    }

    void Settings::set(const std::string& key, const std::string& value)
    {
        try
        {
            _p->settings[nlohmann::json::json_pointer(key)] = value;
        }
        catch (const std::exception&)
        {}
    }
}