// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/IPopup.h>

#include <ftk/Ui/IPopup.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    void iPopup(py::module_& m)
    {
        py::class_<IPopup, IWidget, std::shared_ptr<IPopup> >(m, "IPopup")
            .def("close", &IPopup::close);
    }
}