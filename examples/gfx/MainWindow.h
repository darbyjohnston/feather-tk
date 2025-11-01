// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <ftk/UI/MainWindow.h>
#include <ftk/UI/TabWidget.h>

namespace gfx
{
    class App;

    //! Main window.
    class MainWindow : public ftk::MainWindow
    {
    protected:
        void _init(
            const std::shared_ptr<ftk::Context>&,
            const std::shared_ptr<App>&,
            const ftk::Size2I&);

        MainWindow() = default;

    public:
        virtual ~MainWindow();

        //! Create a new window.
        static std::shared_ptr<MainWindow> create(
            const std::shared_ptr<ftk::Context>&,
            const std::shared_ptr<App>&,
            const ftk::Size2I&);
 
    private:
        std::shared_ptr<ftk::TabWidget> _tabWidget;
    };
}
