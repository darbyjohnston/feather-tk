// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/ProgressDialog.h>
#include <feather-tk/ui/MainWindow.h>
#include <feather-tk/ui/Settings.h>

#include <feather-tk/core/Timer.h>

using namespace ftk;

class DialogsWindow : public MainWindow
{
protected:
    void _init(
        const std::shared_ptr<Context>&,
        const std::shared_ptr<App>&,
        const std::string& name,
        const Size2I&);

    DialogsWindow() = default;

public:
    virtual ~DialogsWindow();

    static std::shared_ptr<Window> create(
        const std::shared_ptr<Context>&,
        const std::shared_ptr<App>&,
        const std::string& name,
        const Size2I&);

private:
    std::shared_ptr<Settings> _settings;
    std::shared_ptr<Timer> _progressTimer;
    std::shared_ptr<ProgressDialog> _progressDialog;
};