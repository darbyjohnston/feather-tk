// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/ui/IDialog.h>

namespace ftk
{
    //! \name Dialogs
    ///@{

    //! Confirmation dialog.
    class ConfirmDialog : public IDialog
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::string& title,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent);

        ConfirmDialog();

    public:
        virtual ~ConfirmDialog();

        //! Create a new widget.
        static std::shared_ptr<ConfirmDialog> create(
            const std::shared_ptr<Context>&,
            const std::string& title,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Set the callback.
        void setCallback(const std::function<void(bool)>&);

    private:
        FTK_PRIVATE();
    };

    ///@}
}