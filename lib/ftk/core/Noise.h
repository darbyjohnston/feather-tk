// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <vector>

namespace ftk
{
    //! \name Noise
    ///@{
        
    //! Noise
    //! 
    //! References:
    //! - https://mrl.cs.nyu.edu/~perlin/noise/
    class Noise
    {
    public:
        Noise();

        double get(double x, double y, double z);

    private:
        std::vector<int> _p;
    };

    ///@}
}
