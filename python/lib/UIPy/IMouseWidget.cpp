// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <UIPy/IMouseWidget.h>

#include <ftk/UI/IMouseWidget.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    void iMouseWidget(py::module_& m)
    {
        py::class_<IMouseWidget, std::shared_ptr<IMouseWidget>>(m, "IMouseWidget");
    }
}