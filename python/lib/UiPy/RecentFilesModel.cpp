// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/RecentFilesModel.h>

#include <ftk/Ui/RecentFilesModel.h>

#include <ftk/Core/Context.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    void recentFilesModel(py::module_& m)
    {
        py::class_<RecentFilesModel, std::shared_ptr<RecentFilesModel> >(m, "RecentFilesModel")
            .def(
                py::init(&RecentFilesModel::create),
                py::arg("context"))
            .def_property(
                "recentMax",
                &RecentFilesModel::getRecentMax,
                &RecentFilesModel::setRecentMax)
            .def("observeRecentMax", &RecentFilesModel::observeRecentMax)
            .def_property(
                "recent",
                &RecentFilesModel::getRecent,
                &RecentFilesModel::setRecent)
            .def("observeRecent", &RecentFilesModel::observeRecent)
            .def("addRecent", &RecentFilesModel::addRecent);
    }
}