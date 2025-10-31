// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <ftk/UI/IDialog.h>

#include <ftk/Core/ISystem.h>

namespace ftk
{
    class ConfirmDialog;
    class MessageDialog;

    //! \name Dialogs
    ///@{

    //! Dialog system.
    class DialogSystem : public ISystem
    {
    protected:
        DialogSystem(const std::shared_ptr<Context>&);

    public:
        virtual ~DialogSystem();

        //! Create a new system.
        static std::shared_ptr<DialogSystem> create(
            const std::shared_ptr<Context>&);

        //! Open a message dialog.
        std::shared_ptr<MessageDialog> message(
            const std::string& title,
            const std::string& text,
            const std::shared_ptr<IWindow>& window);

        //! Open a confirmation dialog.
        std::shared_ptr<ConfirmDialog> confirm(
            const std::string& title,
            const std::string& text,
            const std::shared_ptr<IWindow>& window,
            const std::function<void(bool)>& callback,
            const std::string& confirm = "OK",
            const std::string& cancel = "Cancel");

    private:
        FTK_PRIVATE();
    };

    ///@}
}