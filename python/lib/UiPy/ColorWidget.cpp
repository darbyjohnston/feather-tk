// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/ColorWidget.h>

#include <ftk/Ui/ColorWidget.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    void colorWidget(py::module_& m)
    {
        py::class_<ColorWidget, IWidget, std::shared_ptr<ColorWidget> >(m, "ColorWidget")
            .def(
                py::init(&ColorWidget::create),
                py::arg("context"),
                py::arg("parent") = nullptr)
            .def_property("color", &ColorWidget::getColor, &ColorWidget::setColor)
            .def("setCallback", &ColorWidget::setCallback);
    }
}
