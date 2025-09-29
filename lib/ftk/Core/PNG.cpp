// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/Core/PNGPrivate.h>

#include <filesystem>

namespace ftk
{
    namespace png
    {
        ImagePlugin::ImagePlugin() :
            IImagePlugin("PNG")
        {}

        ImagePlugin::~ImagePlugin()
        {}

        bool ImagePlugin::canRead(
            const std::filesystem::path& path,
            const ImageIOOptions&)
        {
            return compare(
                path.extension().u8string(),
                ".png",
                CaseCompare::Insensitive);
        }

        std::shared_ptr<IImageReader> ImagePlugin::read(
            const std::filesystem::path& path,
            const ImageIOOptions& options)
        {
            return std::shared_ptr<ImageReader>(
                new ImageReader(path, nullptr, options));
        }

        std::shared_ptr<IImageReader> ImagePlugin::read(
            const std::filesystem::path& path,
            const InMemoryFile& memory,
            const ImageIOOptions& options)
        {
            return std::shared_ptr<ImageReader>(
                new ImageReader(path, &memory, options));
        }

        bool ImagePlugin::canWrite(
            const std::filesystem::path& path,
            const ImageInfo& info,
            const ImageIOOptions&)
        {
            return compare(
                path.extension().u8string(),
                ".png",
                CaseCompare::Insensitive) &&
                (
                    info.type == ImageType::L_U8 ||
                    info.type == ImageType::L_U16 ||
                    info.type == ImageType::LA_U8 ||
                    info.type == ImageType::LA_U16 ||
                    info.type == ImageType::RGB_U8 ||
                    info.type == ImageType::RGB_U16 ||
                    info.type == ImageType::RGBA_U8 ||
                    info.type == ImageType::RGBA_U16
                    );
        }

        std::shared_ptr<IImageWriter> ImagePlugin::write(
            const std::filesystem::path& path,
            const ImageInfo& info,
            const ImageIOOptions& options)
        {
            return std::shared_ptr<ImageWriter>(
                new ImageWriter(path, info, options));
        }
    }
}

extern "C"
{
    void pngErrorFunc(png_structp in, png_const_charp msg)
    {
        auto error = reinterpret_cast<ftk::png::ErrorStruct*>(png_get_error_ptr(in));
        error->message = msg;
        longjmp(png_jmpbuf(in), 1);
    }

    void pngWarningFunc(png_structp in, png_const_charp msg)
    {
        auto error = reinterpret_cast<ftk::png::ErrorStruct*>(png_get_error_ptr(in));
        error->message = msg;
    }
}

