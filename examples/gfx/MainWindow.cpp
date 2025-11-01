// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#include "MainWindow.h"

#include "App.h"
#include "GOL.h"
#include "Noise.h"

using namespace ftk;

namespace gfx
{
    void MainWindow::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<App>& app,
        const Size2I& size)
    {
        ftk::MainWindow::_init(context, app, size);

        _tabWidget = TabWidget::create(context);
        _tabWidget->addTab("Game of Life", GOLWidget::create(context));
        _tabWidget->addTab("Animated Noise", NoiseWidget::create(context));
        setWidget(_tabWidget);
    }

    MainWindow::~MainWindow()
    {}

    std::shared_ptr<MainWindow> MainWindow::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<App>& app,
        const Size2I& size)
    {
        auto out = std::shared_ptr<MainWindow>(new MainWindow);
        out->_init(context, app, size);
        return out;
    }
}
