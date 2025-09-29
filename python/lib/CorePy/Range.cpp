// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <CorePy/Range.h>

#include <ftk/Core/Range.h>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

namespace ftk
{
    void range(py::module_& m)
    {
        py::class_<RangeI>(m, "RangeI")
            .def(py::init<>())
            .def(py::init<int, int>())
            .def_property_readonly("min", &RangeI::min)
            .def_property_readonly("max", &RangeI::max)
            .def(pybind11::self == pybind11::self)
            .def(pybind11::self != pybind11::self);

        py::class_<RangeF>(m, "RangeF")
            .def(py::init<>())
            .def(py::init<float, float>())
            .def_property_readonly("min", &RangeF::min)
            .def_property_readonly("max", &RangeF::max)
            .def(pybind11::self == pybind11::self)
            .def(pybind11::self != pybind11::self);

        py::class_<RangeD>(m, "RangeD")
            .def(py::init<>())
            .def(py::init<double, double>())
            .def_property_readonly("min", &RangeD::min)
            .def_property_readonly("max", &RangeD::max)
            .def(pybind11::self == pybind11::self)
            .def(pybind11::self != pybind11::self);
    }
}
