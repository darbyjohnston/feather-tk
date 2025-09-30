// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <UIPy/ConfirmDialog.h>

#include <ftk/UI/ConfirmDialog.h>
#include <ftk/UI/Window.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    void confirmDialog(py::module_& m)
    {
        py::class_<ConfirmDialog, IDialog, std::shared_ptr<ConfirmDialog> >(m, "ConfirmDialog")
            .def(
                py::init(&ConfirmDialog::create),
                py::arg("context"),
                py::arg("title"),
                py::arg("text"),
                py::arg("parent") = nullptr)
            .def("setCallback", &ConfirmDialog::setCallback);
    }
}