// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "Settings.h"

using namespace ftk;

namespace examples
{
    namespace textedit
    {
        bool WindowSettings::operator == (const WindowSettings& other) const
        {
            return
                settings == other.settings &&
                split == other.split;
        }

        bool WindowSettings::operator != (const WindowSettings& other) const
        {
            return !(*this == other);
        }

        bool StyleSettings::operator == (const StyleSettings& other) const
        {
            return
                displayScale == other.displayScale &&
                colorStyle == other.colorStyle;
        }

        bool StyleSettings::operator != (const StyleSettings& other) const
        {
            return !(*this == other);
        }

        void to_json(nlohmann::json& json, const WindowSettings& value)
        {
            json["Settings"] = value.settings;
            json["Split"] = value.split;
        }

        void to_json(nlohmann::json& json, const StyleSettings& value)
        {
            json["DisplayScale"] = value.displayScale;
            json["ColorStyle"] = value.colorStyle;
        }

        void from_json(const nlohmann::json& json, WindowSettings& value)
        {
            json.at("Settings").get_to(value.settings);
            json.at("Split").get_to(value.split);
        }

        void from_json(const nlohmann::json& json, StyleSettings& value)
        {
            json.at("DisplayScale").get_to(value.displayScale);
            json.at("ColorStyle").get_to(value.colorStyle);
        }
    }
}
