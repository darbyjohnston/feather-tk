// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/IPopup.h>

namespace ftk
{
    class IWindow;

    //! \name Dialogs
    ///@{

    //! Base class for dialog widgets.
    class IDialog : public IPopup
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::string& objectName,
            const std::shared_ptr<IWidget>& parent = nullptr);

        IDialog();

    public:
        virtual ~IDialog() = 0;

        //! Open the dialog.
        //!
        //! \todo Should setVisible() be used instead of open() and
        //! close()?
        void open(const std::shared_ptr<IWindow>&);

        //! Get whether the dialog is open.
        bool isOpen() const;

        //! Set the close callback.
        void setCloseCallback(const std::function<void(void)>&);

        void close() override;

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;
        void clipEvent(const Box2I&, bool) override;
        void drawEvent(const Box2I&, const DrawEvent&) override;
        void scrollEvent(ScrollEvent&) override;
        void keyPressEvent(KeyEvent&) override;
        void keyReleaseEvent(KeyEvent&) override;

    private:
        FTK_PRIVATE();
    };

    ///@}
}
