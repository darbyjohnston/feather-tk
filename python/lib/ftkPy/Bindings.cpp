// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#include <CorePy/Bindings.h>
#include <UIPy/Bindings.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(ftkPy, m)
{
    m.doc() = "A lightweight toolkit for building cross-platform applications.";
    ftk::coreBind(m);
    ftk::uiBind(m);
}
