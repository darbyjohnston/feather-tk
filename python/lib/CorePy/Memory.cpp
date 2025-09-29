// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <corePy/Memory.h>

#include <ftk/Core/Memory.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    void memory(py::module_& m)
    {
        m.attr("kilobyte") = kilobyte;
        m.attr("megabyte") = megabyte;
        m.attr("gigabyte") = gigabyte;
        m.attr("terabyte") = terabyte;

        py::enum_<Endian>(m, "Endian")
            .value("MSB", Endian::MSB)
            .value("LSB", Endian::LSB)
            .export_values();

        m.def("getEndian", &getEndian);
        m.def("oppositeEndian", &opposite);
    }
}