// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/IButton.h>

#include <feather-tk/ui/IButton.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace feather_tk
{
    void iButton(py::module_& m)
    {
        py::class_<IButton, IWidget, std::shared_ptr<IButton> >(m, "IButton")
            .def_property("checkable", &IButton::isCheckable, &IButton::setCheckable)
            .def_property("checked", &IButton::isChecked, &IButton::setChecked)
            .def_property("text", &IButton::getText, &IButton::setText)
            .def_property("fontRole", &IButton::getFontRole, &IButton::setFontRole)
            .def_property("icon", &IButton::getIcon, &IButton::setIcon)
            .def_property("checkedIcon", &IButton::getCheckedIcon, &IButton::setCheckedIcon)
            .def_property("buttonRole", &IButton::getButtonRole, &IButton::setButtonRole)
            .def_property("checkedRole", &IButton::getCheckedRole, &IButton::setCheckedRole)
            .def("setHoveredCallback", &IButton::setHoveredCallback)
            .def("setPressedCallback", &IButton::setPressedCallback)
            .def_property("repeatClick", &IButton::hasRepeatClick, &IButton::setRepeatClick)
            .def("setClickedCallback", &IButton::setClickedCallback)
            .def("setCheckedCallback", &IButton::setCheckedCallback);
    }
}