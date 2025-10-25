// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <UIPy/Window.h>

#include <ftk/UI/App.h>
#include <ftk/UI/MainWindow.h>
#include <ftk/UI/MenuBar.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    void mainWindow(py::module_& m)
    {
        py::class_<MainWindow, Window, std::shared_ptr<MainWindow> >(m, "MainWindow")
            .def(
                py::init(&MainWindow::create),
                py::arg("context"),
                py::arg("app"),
                py::arg("size"))
            .def("getMenuBar", &MainWindow::getMenuBar)
            .def("setWidget", &MainWindow::setWidget);
    }
}