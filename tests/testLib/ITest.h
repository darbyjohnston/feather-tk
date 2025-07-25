// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/Util.h>

#include <memory>
#include <string>

namespace feather_tk
{
    class Context;

    namespace test
    {
        //! Base class for tests.
        class ITest : public std::enable_shared_from_this<ITest>
        {
            FEATHER_TK_NON_COPYABLE(ITest);

        protected:
            ITest(
                const std::shared_ptr<Context>&,
                const std::string& name);

        public:
            virtual ~ITest() = 0;

            const std::string& getName() const;

            virtual void run() = 0;

        protected:
            void _print(const std::string&);
            void _error(const std::string&);

            std::weak_ptr<Context> _context;
            std::string _name;
        };
    }
}

#define FEATHER_TK_TEST_ENUM(ENUM) \
    for (auto i : get##ENUM##Enums()) \
    { \
        _print(Format(#ENUM": {0}").arg(getLabel(i))); \
    } \
    { \
        const ENUM v = ENUM::First; \
        std::stringstream ss; \
        ss << v; \
        ENUM v2; \
        ss >> v2; \
        FEATHER_TK_ASSERT(v == v2); \
    }

