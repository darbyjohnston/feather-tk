// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/MDICanvas.h>

#include <feather-tk/ui/MDICanvas.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace feather_tk
{
    void mdiCanvas(py::module_& m)
    {
        py::class_<MDICanvas, IWidget, std::shared_ptr<MDICanvas> >(m, "MDICanvas")
            .def(
                py::init(&MDICanvas::create),
                py::arg("context"),
                py::arg("parent") = nullptr)
            .def_property("canvasSize", &MDICanvas::getCanvasSize, &MDICanvas::setCanvasSize)
            .def_property("gridSize", &MDICanvas::getGridSize, &MDICanvas::setGridSize)
            .def("addWidget", &MDICanvas::addWidget);
    }
}