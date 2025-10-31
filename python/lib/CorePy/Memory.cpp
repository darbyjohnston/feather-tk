// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#include <CorePy/Memory.h>

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
            .value("LSB", Endian::LSB);

        m.def("getEndian", &getEndian);
        m.def("oppositeEndian", &opposite);
    }
}