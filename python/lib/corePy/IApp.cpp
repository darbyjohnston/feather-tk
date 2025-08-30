// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <corePy/IApp.h>

#include <ftk/core/CmdLine.h>
#include <ftk/core/Context.h>
#include <ftk/core/IApp.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    void iApp(py::module_& m)
    {
        py::class_<IApp, std::shared_ptr<IApp> >(m, "IApp")
            .def("getExeName", &IApp::getExeName)
            .def("getExit", &IApp::getExit)
            .def("getContext", &IApp::getContext)
            .def("run", &IApp::run);
    }
}
