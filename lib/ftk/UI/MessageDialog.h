// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/IDialog.h>

namespace ftk
{
    //! \name Dialogs
    ///@{

    //! Message dialog.
    class MessageDialog : public IDialog
    {
    protected:
        void _init(
            const std::shared_ptr<Context>& context,
            const std::string& title,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent);

        MessageDialog();

    public:
        virtual ~MessageDialog();

        //! Create a new widget.
        static std::shared_ptr<MessageDialog> create(
            const std::shared_ptr<Context>& context,
            const std::string& title,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Set the callback.
        void setCallback(const std::function<void(void)>&);

    private:
        FTK_PRIVATE();
    };

    ///@}
}