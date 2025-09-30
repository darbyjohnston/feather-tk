// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <UIPy/IWidgetPopup.h>

#include <ftk/UI/IWidgetPopup.h>
#include <ftk/UI/IWindow.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    void iWidgetPopup(py::module_& m)
    {
        py::class_<IWidgetPopup, IPopup, std::shared_ptr<IWidgetPopup> >(m, "IWidgetPopup")
            .def("open", &IWidgetPopup::open)
            .def_property_readonly("isOpen", &IWidgetPopup::isOpen)
            .def("setCloseCallback", &IWidgetPopup::setCloseCallback)
            .def_property("widget", &IWidgetPopup::getWidget, &IWidgetPopup::setWidget)
            .def_property("popupRole", &IWidgetPopup::getPopupRole, &IWidgetPopup::setPopupRole);
    }
}