// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include "SettingsModel.h"

#include <ftk/UI/CheckBox.h>
#include <ftk/UI/ComboBox.h>
#include <ftk/UI/IntEdit.h>
#include <ftk/UI/RowLayout.h>
#include <ftk/UI/ScrollWidget.h>
#include <ftk/UI/TextEdit.h>

namespace examples
{
    namespace objview
    {
        class App;

        //! Settings widget.
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

            //! Create a new settings widget.
            static std::shared_ptr<SettingsWidget> create(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<App>&,
                const std::shared_ptr<ftk::IWidget>& parent = nullptr);

            void setGeometry(const ftk::Box2I&) override;
            void sizeHintEvent(const ftk::SizeHintEvent&) override;

        private:
            std::shared_ptr<ftk::CheckBox> _animCheckBox;
            std::shared_ptr<ftk::ComboBox> _colorStyleComboBox;
            std::vector<float> _displayScales;
            std::shared_ptr<ftk::ComboBox> _displayScaleComboBox;
            std::shared_ptr<ftk::ScrollWidget> _scrollWidget;
            std::shared_ptr<ftk::VerticalLayout> _layout;

            std::shared_ptr<ftk::ValueObserver<AnimSettings> > _animSettingsObserver;
            std::shared_ptr<ftk::ValueObserver<StyleSettings> > _styleSettingsObserver;
        };
    }
}