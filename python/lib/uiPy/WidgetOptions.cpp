// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/WidgetOptions.h>

#include <feather-tk/ui/IWidget.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace ftk
{
    void widgetOptions(py::module_& m)
    {
        py::enum_<Orientation>(m, "Orientation")
            .value("Horizontal", Orientation::Horizontal)
            .value("Vertical", Orientation::Vertical)
            .export_values();

        py::enum_<Stretch>(m, "Stretch")
            .value("Fixed", Stretch::Fixed)
            .value("Expanding", Stretch::Expanding)
            .export_values();

        py::enum_<HAlign>(m, "HAlign")
            .value("Fill", HAlign::Fill)
            .value("Left", HAlign::Left)
            .value("Center", HAlign::Center)
            .value("Right", HAlign::Right)
            .export_values();

        py::enum_<VAlign>(m, "VAlign")
            .value("Fill", VAlign::Fill)
            .value("Top", VAlign::Top)
            .value("Center", VAlign::Center)
            .value("Bottom", VAlign::Bottom)
            .export_values();
    }
}