// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/Core/IApp.h>

namespace ftk
{
    namespace tests
    {
        //! Test application.
        class App : public IApp
        {
        protected:
            void _init(
                const std::shared_ptr<Context>&,
                std::vector<std::string>& argv);

            App();

        public:
            virtual ~App();

            static std::shared_ptr<App> create(
                const std::shared_ptr<Context>&,
                std::vector<std::string>&);

            void run() override;
            
        private:
            FTK_PRIVATE();
        };
    }
}

