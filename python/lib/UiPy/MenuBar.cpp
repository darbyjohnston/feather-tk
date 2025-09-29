// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <UiPy/MenuBar.h>

#include <ftk/Ui/MenuBar.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    void menuBar(py::module_& m)
    {
        py::class_<MenuBar, IWidget, std::shared_ptr<MenuBar> >(m, "MenuBar")
            .def(
                py::init(&MenuBar::create),
                py::arg("context"),
                py::arg("parent") = nullptr)
            .def(
                "addMenu",
                &MenuBar::addMenu,
                py::arg("text"),
                py::arg("menu"))
            .def(
                "getMenu",
                &MenuBar::getMenu,
                py::arg("text"))
            .def("clear", &MenuBar::clear)
            .def(
                "shortcut",
                &MenuBar::shortcut,
                py::arg("key"),
                py::arg("modifiers"));
    }
}