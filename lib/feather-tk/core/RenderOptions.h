// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/Color.h>
#include <feather-tk/core/Image.h>
#include <feather-tk/core/Memory.h>

#include <iostream>
#include <string>
#include <vector>

namespace ftk
{
    //! \name Rendering
    ///@{

    //! Render options.
    struct RenderOptions
    {
        //! Clear the canvas before rendering.
        bool clear = true;

        //! Clear color.
        Color4F clearColor = Color4F(0.F, 0.F, 0.F, 0.F);

        //! Texture cache byte count.
        size_t textureCacheByteCount = gigabyte / 4;

        //! Glyph texture atlas size.
        int glyphAtlasSize =
#if defined(FTK_API_GLES_2)
            2048;
#else // FTK_API_GLES_2
            4096;
#endif // FTK_API_GLES_2

        //! Enable logging.
        bool log = true;

        bool operator == (const RenderOptions&) const;
        bool operator != (const RenderOptions&) const;
    };

    //! Line drawing options.
    struct LineOptions
    {
        float width = 1.F;

        bool operator == (const LineOptions&) const;
        bool operator != (const LineOptions&) const;
    };

    //! Channel display.
    enum class ChannelDisplay
    {
        Color,
        Red,
        Green,
        Blue,
        Alpha,

        Count,
        First = Color
    };
    FTK_ENUM(ChannelDisplay);

    //! Input video levels.
    enum class InputVideoLevels
    {
        FromFile,
        FullRange,
        LegalRange,

        Count,
        First = FromFile
    };
    FTK_ENUM(InputVideoLevels);

    //! Alpha channel blending.
    //!
    //! References:
    //! - https://microsoft.github.io/Win2D/html/PremultipliedAlpha.htm
    enum class AlphaBlend
    {
        None,
        Straight,
        Premultiplied,

        Count,
        First = None
    };
    FTK_ENUM(AlphaBlend);

    //! Image filtering.
    enum class ImageFilter
    {
        Nearest,
        Linear,

        Count,
        First = Nearest
    };
    FTK_ENUM(ImageFilter);

    //! Image filters.
    struct ImageFilters
    {
        ImageFilter minify  = ImageFilter::Linear;
        ImageFilter magnify = ImageFilter::Linear;

        bool operator == (const ImageFilters&) const;
        bool operator != (const ImageFilters&) const;
    };

    //! Image options.
    struct ImageOptions
    {
        ChannelDisplay   channelDisplay = ChannelDisplay::Color;
        InputVideoLevels videoLevels    = InputVideoLevels::FromFile;
        AlphaBlend       alphaBlend     = AlphaBlend::Straight;
        ImageFilters     imageFilters;
        bool             cache          = true;

        bool operator == (const ImageOptions&) const;
        bool operator != (const ImageOptions&) const;
    };
        
    void to_json(nlohmann::json&, const ImageFilters&);
    void to_json(nlohmann::json&, const ImageOptions&);

    void from_json(const nlohmann::json&, ImageFilters&);
    void from_json(const nlohmann::json&, ImageOptions&);

    ///@}
}

#include <feather-tk/core/RenderOptionsInline.h>

