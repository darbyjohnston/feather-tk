// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/CheckBox.h>
#include <ftk/UI/ComboBox.h>
#include <ftk/UI/IntEdit.h>
#include <ftk/UI/RowLayout.h>
#include <ftk/UI/TextEdit.h>

namespace examples
{
    namespace textedit
    {
        class App;

        class SettingsWidget : public ftk::IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<App>&,
                const std::shared_ptr<ftk::IWidget>& parent);

            SettingsWidget() = default;

        public:
            virtual ~SettingsWidget();

            static std::shared_ptr<SettingsWidget> create(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<App>&,
                const std::shared_ptr<ftk::IWidget>& parent = nullptr);

            void setGeometry(const ftk::Box2I&) override;
            void sizeHintEvent(const ftk::SizeHintEvent&) override;

        private:
            std::shared_ptr<ftk::CheckBox> _lineNumbersCheckBox;
            std::shared_ptr<ftk::ComboBox> _fontComboBox;
            std::shared_ptr<ftk::IntEdit> _fontSizeEdit;
            std::shared_ptr<ftk::VerticalLayout> _layout;

            std::shared_ptr<ftk::ValueObserver<ftk::TextEditOptions> > _textEditOptionsObserver;
        };
    }
}