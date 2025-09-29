// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/Ui/IDialog.h>

#include <ftk/Core/ISystem.h>

namespace ftk
{
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
        void message(
            const std::string& title,
            const std::string& text,
            const std::shared_ptr<IWindow>& window);

        //! Open a confirmation dialog.
        void confirm(
            const std::string& title,
            const std::string& text,
            const std::shared_ptr<IWindow>& window,
            const std::function<void(bool)>& callback);

    private:
        FTK_PRIVATE();
    };

    ///@}
}