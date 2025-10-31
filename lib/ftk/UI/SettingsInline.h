// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

namespace ftk
{
    template<typename T>
    inline bool Settings::getT(const std::string& key, T& value) const
    {
        bool out = false;
        nlohmann::json json;
        if (get(key, json))
        {
            try
            {
                from_json(json, value);
                out = true;
            }
            catch (const std::exception&)
            {}
        }
        return out;
    }

    template<typename T>
    inline void Settings::setT(const std::string& key, const T& value)
    {
        nlohmann::json json;
        to_json(json, value);
        set(key, json);
    }
}
