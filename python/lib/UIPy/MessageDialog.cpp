// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <UIPy/MessageDialog.h>

#include <ftk/UI/MessageDialog.h>
#include <ftk/UI/Window.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    void messageDialog(py::module_& m)
    {
        py::class_<MessageDialog, IDialog, std::shared_ptr<MessageDialog> >(m, "MessageDialog")
            .def(
                py::init(&MessageDialog::create),
                py::arg("context"),
                py::arg("title"),
                py::arg("text"),
                py::arg("parent") = nullptr)
            .def("setCallback", &MessageDialog::setCallback);
    }
}