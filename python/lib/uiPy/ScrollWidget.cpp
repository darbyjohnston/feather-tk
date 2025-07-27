// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/ScrollWidget.h>

#include <feather-tk/ui/ScrollWidget.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace feather_tk
{
    void scrollWidget(py::module_& m)
    {
        py::class_<ScrollWidget, IWidget, std::shared_ptr<ScrollWidget> >(m, "ScrollWidget")
            .def(
                py::init(&ScrollWidget::create),
                py::arg("context"),
                py::arg("type") = ScrollType::Both,
                py::arg("parent") = nullptr)
            .def_property("widget", &ScrollWidget::getWidget, &ScrollWidget::setWidget)
            .def_property_readonly("viewport", &ScrollWidget::getViewport)
            .def_property("scrollType", &ScrollWidget::getScrollType, &ScrollWidget::setScrollType)
            .def_property_readonly("scrollSize", &ScrollWidget::getScrollSize)
            .def_property("scrollPos", &ScrollWidget::getScrollPos, &ScrollWidget::setScrollPos)
            .def("setScrollPosCallback", &ScrollWidget::setScrollPosCallback)
            .def_property("scrollBarsVisible", &ScrollWidget::areScrollBarsVisible, &ScrollWidget::setScrollBarsVisible)
            .def_property("scrollBarsAutoHide", &ScrollWidget::getScrollBarsAutoHide, &ScrollWidget::setScrollBarsAutoHide)
            .def("setScrollEventsEnabled", &ScrollWidget::setScrollEventsEnabled)
            .def_property("border", &ScrollWidget::hasBorder, &ScrollWidget::setBorder)
            .def_property("marginRole", &ScrollWidget::getMarginRole, &ScrollWidget::setMarginRole);
    }
}