// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/Core/Util.h>

#include <memory>
#include <vector>

namespace ftk
{
    //! Random numbers.
    class Random
    {
    public:
        Random();

        ~Random();

        //! Get a random number between zero and one.
        float getF();

        //! Get a random number between zero and the given value.
        float getF(float);

        //! Get a random number between two values.
        float getF(float min, float max);

        //! Get a random number between zero and the given value.
        int getI(int);

        //! Get a random number between two values.
        int getI(int min, int max);

        //! Get a random item from a list.
        template<typename T>
        const T& getItem(const std::vector<T>&);

        //! Seed the random value generator.
        void setSeed(unsigned int);

        //! Seed the random value generator with the current time.
        void setSeed();

    private:
        FTK_PRIVATE();
    };
}

#include <ftk/Core/RandomInline.h>
