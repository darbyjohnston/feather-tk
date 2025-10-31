// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#include <ftk/Core/Vector.h>

namespace ftk
{
    void to_json(nlohmann::json& json, const V2I& value)
    {
        json = { value.x, value.y };
    }

    void to_json(nlohmann::json& json, const V2F& value)
    {
        json = { value.x, value.y };
    }

    void to_json(nlohmann::json& json, const V3F& value)
    {
        json = { value.x, value.y, value.z };
    }

    void to_json(nlohmann::json& json, const V4F& value)
    {
        json = { value.x, value.y, value.z, value.w };
    }

    void from_json(const nlohmann::json& json, V2I& value)
    {
        json.at(0).get_to(value.x);
        json.at(1).get_to(value.y);
    }

    void from_json(const nlohmann::json& json, V2F& value)
    {
        json.at(0).get_to(value.x);
        json.at(1).get_to(value.y);
    }

    void from_json(const nlohmann::json& json, V3F& value)
    {
        json.at(0).get_to(value.x);
        json.at(1).get_to(value.y);
        json.at(2).get_to(value.z);
    }

    void from_json(const nlohmann::json& json, V4F& value)
    {
        json.at(0).get_to(value.x);
        json.at(1).get_to(value.y);
        json.at(2).get_to(value.z);
        json.at(3).get_to(value.w);
    }
}
