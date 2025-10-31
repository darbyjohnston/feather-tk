// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#include <UIPy/WidgetOptions.h>

#include <ftk/UI/IWidget.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace ftk
{
    void widgetOptions(py::module_& m)
    {
        py::enum_<Orientation>(m, "Orientation")
            .value("Horizontal", Orientation::Horizontal)
            .value("Vertical", Orientation::Vertical);

        py::enum_<Stretch>(m, "Stretch")
            .value("Fixed", Stretch::Fixed)
            .value("Expanding", Stretch::Expanding);

        py::enum_<HAlign>(m, "HAlign")
            .value("Fill", HAlign::Fill)
            .value("Left", HAlign::Left)
            .value("Center", HAlign::Center)
            .value("Right", HAlign::Right);

        py::enum_<VAlign>(m, "VAlign")
            .value("Fill", VAlign::Fill)
            .value("Top", VAlign::Top)
            .value("Center", VAlign::Center)
            .value("Bottom", VAlign::Bottom);
    }
}