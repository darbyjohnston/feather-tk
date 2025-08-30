// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/MDIWidget.h>

#include <ftk/ui/MDIWidget.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    void mdiWidget(py::module_& m)
    {
        py::enum_<MDIResize>(m, "MDIResize")
            .value("NoneMDIResize", MDIResize::None)
            .value("North", MDIResize::North)
            .value("NorthEast", MDIResize::NorthEast)
            .value("East", MDIResize::East)
            .value("SouthEast", MDIResize::SouthEast)
            .value("South", MDIResize::South)
            .value("SouthWest", MDIResize::SouthWest)
            .value("West", MDIResize::West)
            .value("NorthWest", MDIResize::NorthWest)
            .export_values();

        py::class_<MDIWidget, IWidget, std::shared_ptr<MDIWidget> >(m, "MDIWidget")
            .def(
                py::init(&MDIWidget::create),
                py::arg("context"),
                py::arg("title"),
                py::arg("parent") = nullptr)
            .def_property("title", &MDIWidget::getTitle, &MDIWidget::setTitle)
            .def_property("widget", &MDIWidget::getWidget, &MDIWidget::setWidget)
            .def("setPressCallback", &MDIWidget::setPressCallback)
            .def("setMoveCallback", &MDIWidget::setMoveCallback)
            .def("setResizeCallback", &MDIWidget::setResizeCallback);
    }
}