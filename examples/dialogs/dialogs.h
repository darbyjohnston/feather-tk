// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/App.h>
#include <ftk/UI/ProgressDialog.h>
#include <ftk/UI/MainWindow.h>
#include <ftk/UI/Settings.h>

#include <ftk/Core/Timer.h>

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