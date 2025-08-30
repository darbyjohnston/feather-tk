// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/IDialog.h>

#include <feather-tk/core/ISystem.h>

#include <filesystem>

namespace ftk
{
    class RecentFilesModel;

    //! \name File Widgets
    ///@{

    //! File browser mode.
    enum class FileBrowserMode
    {
        File,
        Dir,

        Count,
        First = File
    };
    FTK_ENUM(FileBrowserMode);

    //! File browser directory sorting.
    enum class FileBrowserSort
    {
        Name,
        Extension,
        Size,
        Time,

        Count,
        First = Name
    };
    FTK_ENUM(FileBrowserSort);

    //! File browser options.
    struct FileBrowserOptions
    {
        bool                        panel       = true;
        bool                        pathEdit    = false;
        FileBrowserSort             sort        = FileBrowserSort::Name;
        bool                        reverseSort = false;
        bool                        hidden      = false;
        std::map<std::string, bool> bellows =
        {
            { "Drives",    true },
            { "Shortcuts", true },
            { "Recent",    true },
            { "Settings",  false }
        };

        bool operator == (const FileBrowserOptions&) const;
        bool operator != (const FileBrowserOptions&) const;
    };

    //! File browser model.
    class FileBrowserModel : public std::enable_shared_from_this<FileBrowserModel>
    {
    public:
        FileBrowserModel(const std::shared_ptr<Context>&);

    public:
        ~FileBrowserModel();

        //! Create a new model.
        static std::shared_ptr<FileBrowserModel> create(
            const std::shared_ptr<Context>&);

        //! Get the current path.
        const std::filesystem::path& getPath() const;

        //! Observe the current path.
        std::shared_ptr<IObservableValue<std::filesystem::path> > observePath() const;

        //! Set the current path.
        void setPath(const std::filesystem::path&);

        //! Go forward to the next path.
        void forward();

        //! Observe whether there is a next path.
        std::shared_ptr<IObservableValue<bool> > observeHasForward() const;

        //! Go back to the previous path.
        void back();

        //! Observe whether there is a previous path.
        std::shared_ptr<IObservableValue<bool> > observeHasBack() const;

        //! Get the options.
        const FileBrowserOptions& getOptions() const;

        //! Observe the options.
        std::shared_ptr<IObservableValue<FileBrowserOptions> > observeOptions() const;

        //! Set the options.
        void setOptions(const FileBrowserOptions&);

        //! Get the extensions.
        const std::vector<std::string>& getExtensions() const;

        //! Observe the extensions.
        std::shared_ptr<IObservableList<std::string> > observeExtensions() const;

        //! Set the extensions.
        void setExtensions(const std::vector<std::string>&);

        //! Get the current extension.
        const std::string& getExtension() const;

        //! Observe the current extension.
        std::shared_ptr<IObservableValue<std::string> > observeExtension() const;

        //! Set the current extension.
        void setExtension(const std::string&);

    private:
        FTK_PRIVATE();
    };

    //! File browser widget.
    class FileBrowserWidget : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::filesystem::path&,
            FileBrowserMode,
            const std::shared_ptr<FileBrowserModel>& model,
            const std::shared_ptr<IWidget>& parent);

        FileBrowserWidget();

    public:
        virtual ~FileBrowserWidget();

        //! Create a new widget.
        static std::shared_ptr<FileBrowserWidget> create(
            const std::shared_ptr<Context>&,
            const std::filesystem::path& fileName = std::filesystem::path(),
            FileBrowserMode = FileBrowserMode::File,
            const std::shared_ptr<FileBrowserModel>& model = nullptr,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Set the callback.
        void setCallback(const std::function<void(const std::filesystem::path&)>&);

        //! Set the cancel callback.
        void setCancelCallback(const std::function<void(void)>&);

        //! Get the file browser model.
        const std::shared_ptr<FileBrowserModel>& getModel() const;

        //! Get the recent files model.
        const std::shared_ptr<RecentFilesModel>& getRecentFilesModel() const;

        //! Set the recent files model.
        void setRecentFilesModel(const std::shared_ptr<RecentFilesModel>&);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        void _optionsUpdate();
        void _extensionsUpdate();

        FTK_PRIVATE();
    };

    //! File browser dialog.
    class FileBrowser : public IDialog
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::filesystem::path&,
            FileBrowserMode,
            const std::shared_ptr<FileBrowserModel>& model,
            const std::shared_ptr<IWidget>& parent);

        FileBrowser();

    public:
        virtual ~FileBrowser();

        //! Create a new dialog.
        static std::shared_ptr<FileBrowser> create(
            const std::shared_ptr<Context>&,
            const std::filesystem::path& fileName = std::filesystem::path(),
            FileBrowserMode = FileBrowserMode::File,
            const std::shared_ptr<FileBrowserModel>& model = nullptr,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Set the callback.
        void setCallback(const std::function<void(const std::filesystem::path&)>&);

        //! Get the file browser model.
        const std::shared_ptr<FileBrowserModel>& getModel() const;

        //! Get the recent files model.
        const std::shared_ptr<RecentFilesModel>& getRecentFilesModel() const;

        //! Set the recent files model.
        void setRecentFilesModel(const std::shared_ptr<RecentFilesModel>&);

    private:
        FTK_PRIVATE();
    };

    //! File browser system.
    class FileBrowserSystem : public ISystem
    {
    protected:
        FileBrowserSystem(const std::shared_ptr<Context>&);

    public:
        virtual ~FileBrowserSystem();

        //! Create a new system.
        static std::shared_ptr<FileBrowserSystem> create(
            const std::shared_ptr<Context>&);

        //! Open the file browser.
        void open(
            const std::shared_ptr<IWindow>&,
            const std::function<void(const std::filesystem::path&)>&,
            const std::filesystem::path& fileName = std::filesystem::path(),
            FileBrowserMode = FileBrowserMode::File);

        //! Get whether the native file dialog is used.
        bool isNativeFileDialog() const;

        //! Set whether the native file dialog is used.
        void setNativeFileDialog(bool);

        //! Get the file browser model.
        const std::shared_ptr<FileBrowserModel>& getModel() const;

        //! Get the recent files model.
        const std::shared_ptr<RecentFilesModel>& getRecentFilesModel() const;

        //! Set the recent files model.
        void setRecentFilesModel(const std::shared_ptr<RecentFilesModel>&);

    private:
        FTK_PRIVATE();
    };

    void to_json(nlohmann::json&, const FileBrowserOptions&);

    void from_json(const nlohmann::json&, FileBrowserOptions&);

    ///@}
}
