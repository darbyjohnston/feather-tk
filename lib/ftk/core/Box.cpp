// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/core/Box.h>

namespace ftk
{
    void to_json(nlohmann::json& json, const Box2I& value)
    {
        json = { value.min, value.max };
    }

    void to_json(nlohmann::json& json, const Box2F& value)
    {
        json = { value.min, value.max };
    }

    void to_json(nlohmann::json& json, const Box3F& value)
    {
        json = { value.min, value.max };
    }

    void from_json(const nlohmann::json& json, Box2I& value)
    {
        json.at(0).get_to(value.min);
        json.at(1).get_to(value.max);
    }

    void from_json(const nlohmann::json& json, Box2F& value)
    {
        json.at(0).get_to(value.min);
        json.at(1).get_to(value.max);
    }

    void from_json(const nlohmann::json& json, Box3F& value)
    {
        json.at(0).get_to(value.min);
        json.at(1).get_to(value.max);
    }
}
