// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/IntModel.h>

#include <ftk/ui/IntModel.h>

#include <ftk/core/Context.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    void intModel(py::module_& m)
    {
        py::class_<IntModel, std::shared_ptr<IntModel> >(m, "IntModel")
            .def(py::init(&IntModel::create),
                py::arg("context"));
    }
}