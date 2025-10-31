// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <pybind11/pybind11.h>

namespace ftk
{
    template<typename T>
    void observableValue(pybind11::module_&, const std::string& type);
    void observableValue(pybind11::module_&);
}

#include <CorePy/ObservableValueInline.h>
