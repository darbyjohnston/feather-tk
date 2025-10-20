// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/App.h>

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

        //! Render modes.
        enum class RenderMode
        {
            Shaded,
            Flat,
            Texture,
            Normals,

            Count,
            First = Shaded
        };
        FTK_ENUM(RenderMode);

        //! Render settigns.
        struct RenderSettings
        {
            RenderMode mode = RenderMode::Shaded;
            bool       cull = true;

            bool operator == (const RenderSettings&) const;
            bool operator != (const RenderSettings&) const;
        };

        //! Animation settings.
        struct AnimSettings
        {
            bool enabled = true;

            bool operator == (const AnimSettings&) const;
            bool operator != (const AnimSettings&) const;
        };

        //! Style settings.
        struct StyleSettings
        {
            float displayScale = 2.F;
            ftk::ColorStyle colorStyle = ftk::ColorStyle::Dark;

            bool operator == (const StyleSettings&) const;
            bool operator != (const StyleSettings&) const;
        };

        void to_json(nlohmann::json&, const WindowSettings&);
        void to_json(nlohmann::json&, const RenderSettings&);
        void to_json(nlohmann::json&, const AnimSettings&);
        void to_json(nlohmann::json&, const StyleSettings&);

        void from_json(const nlohmann::json&, WindowSettings&);
        void from_json(const nlohmann::json&, RenderSettings&);
        void from_json(const nlohmann::json&, AnimSettings&);
        void from_json(const nlohmann::json&, StyleSettings&);
    }
}