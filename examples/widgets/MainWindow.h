// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/App.h>
#include <ftk/UI/MainWindow.h>
#include <ftk/UI/TabWidget.h>

using namespace ftk;

namespace widgets
{
    class MainWindow : public ftk::MainWindow
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<App>&);

        MainWindow() = default;

    public:
        virtual ~MainWindow();

        static std::shared_ptr<MainWindow> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<App>&);

    private:
        std::shared_ptr<ftk::TabWidget> _tabWidget;
    };
}
