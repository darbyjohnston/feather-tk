// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/ButtonGroup.h>

#include <ftk/ui/ButtonGroup.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    void buttonGroup(py::module_& m)
    {
        py::enum_<ButtonGroupType>(m, "ButtonGroupType")
            .value("Click", ButtonGroupType::Click)
            .value("Check", ButtonGroupType::Check)
            .value("Radio", ButtonGroupType::Radio)
            .value("Toggle", ButtonGroupType::Toggle)
            .export_values();

        py::class_<ButtonGroup, std::shared_ptr<ButtonGroup> >(m, "ButtonGroup")
            .def(
                py::init(&ButtonGroup::create),
                py::arg("context"),
                py::arg("type"))
            .def("getButtons", &ButtonGroup::getButtons)
            .def("addButton", &ButtonGroup::addButton)
            .def("clearButtons", &ButtonGroup::clearButtons)
            .def(
                "setChecked",
                &ButtonGroup::setChecked,
                py::arg("index"),
                py::arg("checked"))
            .def("setClickedCallback", &ButtonGroup::setClickedCallback)
            .def("setCheckedCallback", &ButtonGroup::setCheckedCallback);
    }
}