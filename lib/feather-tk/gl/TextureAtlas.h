// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/gl/Texture.h>

#include <feather-tk/core/BoxPack.h>
#include <feather-tk/core/Image.h>
#include <feather-tk/core/Range.h>

namespace ftk
{
    namespace gl
    {
        //! \name Texture Atlas
        ///@{
        
        //! Texture atlas item.
        struct TextureAtlasItem
        {
            BoxPackID id = boxPackInvalidID;
            Size2I size;
            RangeF u;
            RangeF v;
        };

        //! Texture atlas.
        class TextureAtlas : public std::enable_shared_from_this<TextureAtlas>
        {
            FTK_NON_COPYABLE(TextureAtlas);

        protected:
            void _init(
                int size,
                ImageType,
                ImageFilter,
                int border);

            TextureAtlas();

        public:
            ~TextureAtlas();

            //! Create a new texture atlas.
            static std::shared_ptr<TextureAtlas> create(
                int size,
                ImageType,
                ImageFilter = ImageFilter::Linear,
                int border = 1);

            //! Get the texture atlas size.
            int getSize() const;

            //! Get the texture atlas type.
            ImageType getType() const;

            //! Get the texture atlas ID.
            unsigned int getTexture() const;

            //! Get a texture atlas item.
            bool getItem(BoxPackID, TextureAtlasItem&);

            //! Add a texture atlas item.
            bool addItem(const std::shared_ptr<Image>&, TextureAtlasItem&);

            //! Get the percentage of the texture atlas that is in use.
            float getPercentageUsed() const;

        private:
            void _toItem(const std::shared_ptr<BoxPackNode>&, TextureAtlasItem&);

            FTK_PRIVATE();
        };
        
        ///@}
    }
}
