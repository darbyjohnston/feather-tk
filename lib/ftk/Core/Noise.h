// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

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
