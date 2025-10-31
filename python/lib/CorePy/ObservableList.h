// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <pybind11/pybind11.h>

namespace ftk
{
    template<typename T>
    void observableList(pybind11::module_&, const std::string& type);
    void observableList(pybind11::module_&);
}

#include <CorePy/ObservableListInline.h>
