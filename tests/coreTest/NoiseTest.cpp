// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/NoiseTest.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Math.h>
#include <feather-tk/core/Noise.h>

#include <iostream>

namespace ftk
{
    namespace core_test
    {
        NoiseTest::NoiseTest(const std::shared_ptr<Context>& context) :
            ITest(context, "ftk::core_test::NoiseTest")
        {}

        NoiseTest::~NoiseTest()
        {}

        std::shared_ptr<NoiseTest> NoiseTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<NoiseTest>(new NoiseTest(context));
        }
        
        namespace
        {
            char lut(double value)
            {
                const std::vector<char> data =
                {
                    '_',
                    '.',
                    'o',
                    'O',
                    '0',
                    '#'
                };
                return data[static_cast<size_t>(clamp(value, 0.0, 1.0) * 5.99)];
            }
        }

        void NoiseTest::run()
        {
            Noise noise;
            for (int i = 0; i < 40; ++i)
            {
                for (int j = 0; j < 80; ++j)
                {
                    std::cout << lut(10.0 * noise.get(i / 4.0, j / 8.0, 0.0));
                }
                std::cout << std::endl;
            }
        }
    }
}

