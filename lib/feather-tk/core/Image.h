// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/Memory.h>
#include <feather-tk/core/Range.h>
#include <feather-tk/core/Util.h>
#include <feather-tk/core/Vector.h>

#include <iostream>
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace feather_tk
{
    //! \name Images
    ///@{

    //! Image types.
    enum class ImageType
    {
        None,

        L_U8,
        L_U16,
        L_U32,
        L_F16,
        L_F32,

        LA_U8,
        LA_U16,
        LA_U32,
        LA_F16,
        LA_F32,

        RGB_U8,
        RGB_U10,
        RGB_U16,
        RGB_U32,
        RGB_F16,
        RGB_F32,

        RGBA_U8,
        RGBA_U16,
        RGBA_U32,
        RGBA_F16,
        RGBA_F32,

        YUV_420P_U8,
        YUV_422P_U8,
        YUV_444P_U8,

        YUV_420P_U16,
        YUV_422P_U16,
        YUV_444P_U16,

        ARGB_4444_Premult,

        Count,
        First = None
    };
    FEATHER_TK_ENUM(ImageType);

    //! Get the number of channels for the given image type.
    int getChannelCount(ImageType);

    //! Get the bit-depth for the given image type.
    int getBitDepth(ImageType);

    //! Video levels.
    enum class VideoLevels
    {
        FullRange,
        LegalRange,

        Count,
        First = FullRange
    };
    FEATHER_TK_ENUM(VideoLevels);

    //! YUV coefficients.
    enum class YUVCoefficients
    {
        REC709,
        BT2020,

        Count,
        First = REC709
    };
    FEATHER_TK_ENUM(YUVCoefficients);

    //! Get YUV coefficients.
    V4F getYUVCoefficients(YUVCoefficients);

    //! Image mirroring.
    struct ImageMirror
    {
        ImageMirror() = default;
        constexpr ImageMirror(bool x, bool y);

        bool x = false;
        bool y = false;

        constexpr bool operator == (const ImageMirror&) const;
        constexpr bool operator != (const ImageMirror&) const;
    };

    //! Image data layout.
    struct ImageLayout
    {
        ImageLayout() = default;
        ImageLayout(
            const ImageMirror& mirror,
            int                alignment = 1,
            Endian             endian    = getEndian());

        ImageMirror mirror;
        int         alignment = 1;
        Endian      endian    = getEndian();

        constexpr bool operator == (const ImageLayout&) const;
        constexpr bool operator != (const ImageLayout&) const;
    };

    //! Image information.
    struct ImageInfo
    {
        ImageInfo() = default;
        ImageInfo(const Size2I&, ImageType);
        ImageInfo(int w, int h, ImageType);

        std::string     name             = "Default";
        Size2I          size;
        ImageType       type             = ImageType::None;
        float           pixelAspectRatio = 1.F;
        VideoLevels     videoLevels      = VideoLevels::FullRange;
        YUVCoefficients yuvCoefficients  = YUVCoefficients::REC709;
        ImageLayout     layout;

        //! Is the information valid?
        bool isValid() const;
                
        //! Get the aspect ratio.
        float getAspect() const;

        //! Get the number of bytes used to store an image.
        size_t getByteCount() const;

        bool operator == (const ImageInfo&) const;
        bool operator != (const ImageInfo&) const;
    };

    //! Image tags.
    typedef std::map<std::string, std::string> ImageTags;

    //! Image.
    class Image : public std::enable_shared_from_this<Image>
    {
        FEATHER_TK_NON_COPYABLE(Image);

    protected:
        Image(const ImageInfo&, uint8_t* externalData = nullptr);

    public:
        ~Image();

        //! Create a new image.
        static std::shared_ptr<Image> create(const ImageInfo&);

        //! Create a new image.
        static std::shared_ptr<Image> create(const ImageInfo&, uint8_t* externalData);

        //! Create a new image.
        static std::shared_ptr<Image> create(const Size2I&, ImageType);

        //! Create a new image.
        static std::shared_ptr<Image> create(int w, int h, ImageType);

        //! Get the image information.
        const ImageInfo& getInfo() const;
            
        //! Get the image size.
        const Size2I& getSize() const;

        //! Get the image width.
        int getWidth() const;

        //! Get the image height.
        int getHeight() const;

        //! Get the aspect ratio.
        float getAspect() const;

        //! Get the image type.
        ImageType getType() const;

        //! Is the image valid?
        bool isValid() const;

        //! Get the image tags.
        const ImageTags& getTags() const;

        //! Set the image tags.
        void setTags(const ImageTags&);

        //! Get the number of bytes used to store the image data.
        size_t getByteCount() const;

        //! Get the image data.
        const uint8_t* getData() const;

        //! Get the image data.
        uint8_t* getData();

        //! Zero the image data.
        void zero();

    private:
        ImageInfo _info;
        ImageTags _tags;
        size_t _byteCount = 0;
        std::vector<uint8_t> _data;
        uint8_t* _dataP = nullptr;
    };

    void to_json(nlohmann::json&, const ImageMirror&);

    void from_json(const nlohmann::json&, ImageMirror&);

    ///@}
}

#include <feather-tk/core/ImageInline.h>

