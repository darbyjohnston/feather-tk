// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/Window.h>

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/MainWindow.h>
#include <feather-tk/ui/MenuBar.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace feather_tk
{
    void mainWindow(py::module_& m)
    {
        py::class_<MainWindow, Window, std::shared_ptr<MainWindow> >(m, "MainWindow")
            .def(
                py::init(&MainWindow::create),
                py::arg("context"),
                py::arg("app"),
                py::arg("name"),
                py::arg("size"))
            .def("getMenuBar", &MainWindow::getMenuBar)
            .def("setWidget", &MainWindow::setWidget);
    }
}