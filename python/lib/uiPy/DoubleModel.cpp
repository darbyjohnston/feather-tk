// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/DoubleModel.h>

#include <feather-tk/ui/DoubleModel.h>

#include <feather-tk/core/Context.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    void doubleModel(py::module_& m)
    {
        py::class_<DoubleModel, std::shared_ptr<DoubleModel> >(m, "DoubleModel")
            .def(py::init(&DoubleModel::create),
                py::arg("context"));
    }
}