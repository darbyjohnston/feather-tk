// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/ObservableList.h>
#include <feather-tk/core/ObservableValue.h>

#include <filesystem>

namespace ftk
{
    class Context;

    //! \name File Widgets
    ///@{

    //! Recent files model.
    class RecentFilesModel : public std::enable_shared_from_this<RecentFilesModel>
    {
        FTK_NON_COPYABLE(RecentFilesModel);

    protected:
        void _init(const std::shared_ptr<Context>&);

        RecentFilesModel();

    public:
        ~RecentFilesModel();

        //! Create a new model.
        static std::shared_ptr<RecentFilesModel> create(
            const std::shared_ptr<Context>&);

        //! Get the maximum number of recent files.
        size_t getRecentMax() const;

        //! Observe the maximum number of recent files.
        std::shared_ptr<IObservableValue<size_t> > observeRecentMax() const;

        //! Set the maximum number of recent files.
        void setRecentMax(size_t);

        //! Get the list of recent files.
        const std::vector<std::filesystem::path>& getRecent() const;

        //! Observe the list of recent files.
        std::shared_ptr<IObservableList<std::filesystem::path> > observeRecent() const;

        //! Set the recent files.
        void setRecent(const std::vector<std::filesystem::path>&);

        //! Add a recent file.
        void addRecent(const std::filesystem::path&);

    private:
        FTK_PRIVATE();
    };

    ///@}
}