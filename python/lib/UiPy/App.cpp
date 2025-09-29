// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <UiPy/App.h>

#include <ftk/Ui/App.h>
#include <ftk/Ui/Settings.h>
#include <ftk/Ui/Window.h>

#include <ftk/Core/CmdLine.h>
#include <ftk/Core/Context.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace pybind11::literals;
namespace py = pybind11;

namespace ftk
{
    void app(py::module_& m)
    {
        py::class_<App, IApp, std::shared_ptr<App> >(m, "App")
            .def(
                py::init(py::overload_cast<
                    const std::shared_ptr<Context>&,
                    const std::vector<std::string>&,
                    const std::string&,
                    const std::string&,
                    const std::vector<std::shared_ptr<ICmdLineArg> >&,
                    const std::vector<std::shared_ptr<ICmdLineOption> >&>(&App::create)),
                py::arg("context"),
                py::arg("argv"),
                py::arg("name"),
                py::arg("summary"),
                py::arg("cmdLineArgs") = std::vector<std::shared_ptr<ICmdLineArg> >(),
                py::arg("cmdLineOptions") = std::vector<std::shared_ptr<ICmdLineOption> >())
            .def("addWindow", &App::addWindow, py::arg("window"))
            .def("removeWindow", &App::removeWindow, py::arg("window"))
            .def("getWindows", &App::getWindows)
            .def("getFontSystem", &App::getFontSystem)
            .def("getIconSystem", &App::getIconSystem)
            .def("getStyle", &App::getStyle)
            .def("exit", &App::exit);
    }
}
