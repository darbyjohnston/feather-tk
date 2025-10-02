// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include "SettingsModel.h"

#include <ftk/UI/Action.h>

namespace examples
{
    namespace textedit
    {
        class App;

        class Actions : public std::enable_shared_from_this<Actions>
        {
        protected:
            void _init(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<App>&);

            Actions() = default;

        public:
            virtual ~Actions();

            static std::shared_ptr<Actions> create(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<App>&);

            const std::map<std::string, std::shared_ptr<ftk::Action> > getActions() const;

            std::shared_ptr<ftk::Action> getAction(const std::string&) const;

        private:
            void _createFileActions(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<App>&);
            void _createEditActions(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<App>&);

            std::map<std::string, std::shared_ptr<ftk::Action> > _actions;

            std::shared_ptr<ftk::ValueObserver<WindowOptions> > _windowOptionsObserver;
        };
    }
}