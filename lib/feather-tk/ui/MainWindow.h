// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/Window.h>

namespace feather_tk
{
    class App;
    class MenuBar;

    //! Main window.
    class MainWindow : public Window
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<App>&,
            const std::string& name,
            const Size2I&);

        MainWindow();

    public:
        virtual ~MainWindow();

        //! Create a new widget.
        static std::shared_ptr<MainWindow> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<App>&,
            const std::string& name,
            const Size2I& = Size2I(1280, 960));

        //! Get the menu bar.
        const std::shared_ptr<MenuBar>& getMenuBar() const;

        //! Set the central widget.
        void setWidget(const std::shared_ptr<IWidget>&);

        void keyPressEvent(KeyEvent&) override;
        void keyReleaseEvent(KeyEvent&) override;

    private:
        FEATHER_TK_PRIVATE();
    };

    ///@}
}
