// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/ObservableList.h>

#include <filesystem>

namespace ftk
{
    class Context;

    //! \name File Widgets
    ///@{
        
    //! File system drives model.
    class DrivesModel : public std::enable_shared_from_this<DrivesModel>
    {
        FTK_NON_COPYABLE(DrivesModel);

    protected:
        void _init(const std::shared_ptr<Context>&);

        DrivesModel();

    public:
        ~DrivesModel();

        //! Create a new model.
        static std::shared_ptr<DrivesModel> create(
            const std::shared_ptr<Context>&);

        //! Observe the list of drives.
        std::shared_ptr<IObservableList<std::filesystem::path> > observeDrives() const;

    private:
        FTK_PRIVATE();
    };
        
    ///@}
}
