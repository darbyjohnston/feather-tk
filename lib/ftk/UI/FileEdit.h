// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/FileBrowser.h>

#include <filesystem>

namespace ftk
{
    class RecentFilesModel;

    //! \name File Widgets
    ///@{

    //! File edit widget.
    class FileEdit : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            FileBrowserMode,
            const std::shared_ptr<IWidget>& parent);

        FileEdit();

    public:
        virtual ~FileEdit();

        //! Create a new widget.
        static std::shared_ptr<FileEdit> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Create a new widget.
        static std::shared_ptr<FileEdit> create(
            const std::shared_ptr<Context>&,
            FileBrowserMode,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Get the path.
        const std::filesystem::path& getPath() const;

        //! Set the path.
        void setPath(const std::filesystem::path&);

        //! Set the callback.
        void setCallback(const std::function<void(const std::filesystem::path&)>&);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        void _openDialog();
        void _widgetUpdate();

        FTK_PRIVATE();
    };

    ///@}
}
