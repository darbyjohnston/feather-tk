// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#include <UIPy/IDialog.h>

#include <ftk/UI/IDialog.h>
#include <ftk/UI/Window.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    void iDialog(py::module_& m)
    {
        py::class_<IDialog, IPopup, std::shared_ptr<IDialog> >(m, "IDialog")
            .def("open", &IDialog::open)
            .def("isOpen", &IDialog::isOpen)
            .def("setCloseCallback", &IDialog::setCloseCallback);
    }
}