// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <UiPy/IMenuPopup.h>

#include <ftk/Ui/IMenuPopup.h>
#include <ftk/Ui/IWindow.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    void iMenuPopup(py::module_& m)
    {
        py::class_<IMenuPopup, IPopup, std::shared_ptr<IMenuPopup> >(m, "IMenuPopup")
            .def(
                "open",
                &IMenuPopup::open,
                py::arg("window"),
                py::arg("buttonGeometry"))
            .def("isOpen", &IMenuPopup::isOpen)
            .def(
                "setCloseCallback",
                &IMenuPopup::setCloseCallback,
                py::arg("callback"))
            .def(
                "setPopup",
                &IMenuPopup::setPopup,
                py::arg("type"))
            .def(
                "setPopupRole",
                &IMenuPopup::setPopupRole,
                py::arg("role"))
            .def(
                "setWidget",
                &IMenuPopup::setWidget,
                py::arg("widget"));
    }
}