// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <corePy/Random.h>

#include <ftk/Core/Random.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace ftk
{
    void random(py::module_& m)
    {
        py::class_<Random>(m, "Random")
            .def(py::init<>())
            .def("getF", py::overload_cast<>(&Random::getF))
            .def("getF", py::overload_cast<float>(&Random::getF))
            .def("getF", py::overload_cast<float, float>(&Random::getF), py::arg("min"), py::arg("max"))
            .def("getI", py::overload_cast<int>(&Random::getI))
            .def("getI", py::overload_cast<int, int>(&Random::getI), py::arg("min"), py::arg("max"))
            .def("setSeed", py::overload_cast<unsigned int>(&Random::setSeed))
            .def("setSeed", py::overload_cast<>(&Random::setSeed));
    }
}
