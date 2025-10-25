// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <UIPy/Window.h>

#include <ftk/UI/App.h>
#include <ftk/UI/Window.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    class PyWindow : public Window
    {
    public:
        static std::shared_ptr<PyWindow> create(
            const std::shared_ptr<Context>& context,
            const std::string& name,
            const Size2I& size)
        {
            auto out = std::shared_ptr<PyWindow>(new PyWindow);
            out->_init(context, name, size);
            return out;
        }

        virtual void drawEvent(const Box2I& drawRect, const DrawEvent& event) override
        {
            PYBIND11_OVERRIDE(
                void,
                Window,
                drawEvent,
                drawRect,
                event);
        }
    };

    void window(py::module_& m)
    {
        py::class_<Window, IWindow, std::shared_ptr<Window>, PyWindow>(m, "Window")
            .def(
                py::init(&Window::create, &PyWindow::create),
                py::arg("context"),
                py::arg("name"),
                py::arg("size"))
            .def_property_readonly("windowID", &Window::getID)
            .def_property("title", &Window::getTitle, &Window::setTitle)
            .def_property("size", &Window::getSize, &Window::setSize)
            .def_property("fullScreen", &Window::isFullScreen, &Window::setFullScreen)
            .def("observeFullScreen", &Window::observeFullScreen)
            .def_property_readonly("getScreen", &Window::getScreen)
            .def_property("floatOnTop", &Window::isFloatOnTop, &Window::setFloatOnTop)
            .def("observeFloatOnTop", &Window::observeFloatOnTop)
            .def_property_readonly("frameBufferSize", &Window::getFrameBufferSize)
            .def_property("frameBufferType", &Window::getFrameBufferType, &Window::setFrameBufferType)
            .def("observeFrameBufferType", &Window::observeFrameBufferType)
            .def_property_readonly("contentScale", &Window::getContentScale)
            .def_property("displayScale", &Window::getDisplayScale, &Window::setDisplayScale)
            .def("observeDisplayScale", &Window::observeDisplayScale);
    }
}