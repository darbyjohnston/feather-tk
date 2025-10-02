// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include "Document.h"

#include <ftk/UI/TextEdit.h>

namespace examples
{
    namespace textedit
    {
        struct WindowOptions
        {
            bool settings = false;
            float split = .7F;

            bool operator == (const WindowOptions&) const;
            bool operator != (const WindowOptions&) const;
        };

        class SettingsModel : public std::enable_shared_from_this<SettingsModel>
        {
        protected:
            void _init(const std::shared_ptr<ftk::Context>&);

            SettingsModel() = default;

        public:
            virtual ~SettingsModel();

            static std::shared_ptr<SettingsModel> create(
                const std::shared_ptr<ftk::Context>&);

            const WindowOptions& getWindowOptions() const;
            std::shared_ptr<ftk::IObservableValue<WindowOptions> > observeWindowOptions() const;
            void setWindowOptions(const WindowOptions&);

            const ftk::TextEditOptions& getTextEditOptions() const;
            std::shared_ptr<ftk::IObservableValue<ftk::TextEditOptions> > observeTextEditOptions() const;
            void setTextEditOptions(const ftk::TextEditOptions&);

        private:
            std::shared_ptr<ftk::ObservableValue<WindowOptions> > _windowOptions;
            std::shared_ptr<ftk::ObservableValue<ftk::TextEditOptions> > _textEditOptions;
        };
    }
}