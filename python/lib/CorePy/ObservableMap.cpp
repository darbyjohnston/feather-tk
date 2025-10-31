// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#include <CorePy/ObservableMap.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    void observableMap(py::module_& m)
    {
        observableMap<std::string, int>(m, "StringI");
    }
}
