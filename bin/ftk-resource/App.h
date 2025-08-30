// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <chrono>
#include <memory>
#include <string>

//! Resource application.
class App
{
protected:
    void _init(int argc, char** argv);

    App() = default;

public:
    ~App();
            
    static std::shared_ptr<App> create(int argc, char** argv);

    int getExit() const { return _exit; }

    void run();

private:
    int _exit = 0;
    std::string _input;
    std::string _output;
    std::string _namespace;
    std::chrono::steady_clock::time_point _startTime;
};
