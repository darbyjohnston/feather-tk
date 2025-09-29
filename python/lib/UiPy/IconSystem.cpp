// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <UiPy/IconSystem.h>

#include <ftk/Ui/IconSystem.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    void iconSystem(py::module_& m)
    {
        py::class_<IconSystem, ISystem, std::shared_ptr<IconSystem> >(m, "IconSystem")
            .def(
                py::init(&IconSystem::create),
                py::arg("context"))
            .def_property_readonly("names", &IconSystem::getNames)
            .def(
                "add",
                &IconSystem::add,
                py::arg("name"),
                py::arg("svg"))
            .def(
                "get",
                &IconSystem::get,
                py::arg("name"),
                py::arg("displayScale"));
    }
}
