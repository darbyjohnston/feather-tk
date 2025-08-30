// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/IWindow.h>

#include <feather-tk/ui/IWindow.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    class PyIWindow : public IWindow
    {
    public:
        virtual void drawEvent(const Box2I& drawRect, const DrawEvent& event) override
        {
            PYBIND11_OVERRIDE(
                void,
                IWindow,
                drawEvent,
                drawRect,
                event);
        }
    };

    void iWindow(py::module_& m)
    {
        py::class_<IWindow, IWidget, std::shared_ptr<IWindow>, PyIWindow>(m, "IWindow");
    }
}