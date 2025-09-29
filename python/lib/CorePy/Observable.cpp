// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <corePy/Observable.h>

#include <ftk/Core/Observable.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    void observable(py::module_& m)
    {
        py::enum_<ObserverAction>(m, "ObserverAction")
            .value("Trigger", ObserverAction::Trigger)
            .value("Suppress", ObserverAction::Suppress)
            .export_values();
    }
}
