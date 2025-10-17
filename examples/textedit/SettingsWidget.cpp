// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "SettingsWidget.h"

#include "App.h"
#include "SettingsModel.h"

#include <ftk/UI/Divider.h>
#include <ftk/UI/FormLayout.h>
#include <ftk/UI/Label.h>
#include <ftk/UI/ToolButton.h>

using namespace ftk;

namespace examples
{
    namespace textedit
    {
        void SettingsWidget::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "examples::textedit::SettingsWidget", parent);

            auto titleLabel = Label::create(context, "Settings");
            titleLabel->setMarginRole(SizeRole::MarginSmall);
            titleLabel->setHStretch(Stretch::Expanding);
            auto closeButton = ToolButton::create(context);
            closeButton->setIcon("Close");

            _fontComboBox = ComboBox::create(context);
            _fontComboBox->setItems(getFontLabels());
            _fontComboBox->setHStretch(Stretch::Expanding);

            _fontSizeEdit = ftk::IntEdit::create(context);
            _fontSizeEdit->setRange(6, 64);

            _tabSpacesEdit = ftk::IntEdit::create(context);
            _tabSpacesEdit->setRange(1, 8);

            _layout = VerticalLayout::create(context, shared_from_this());
            _layout->setSpacingRole(SizeRole::None);

            auto hLayout = HorizontalLayout::create(context, _layout);
            hLayout->setSpacingRole(SizeRole::None);
            hLayout->setBackgroundRole(ColorRole::Button);
            titleLabel->setParent(hLayout);
            closeButton->setParent(hLayout);

            auto formLayout = FormLayout::create(context, _layout);
            formLayout->setMarginRole(SizeRole::Margin);
            hLayout = HorizontalLayout::create(context);
            hLayout->setSpacingRole(SizeRole::SpacingSmall);
            _fontComboBox->setParent(hLayout);
            _fontSizeEdit->setParent(hLayout);
            formLayout->addRow("Font:", hLayout);
            formLayout->addRow("Tab spaces:", _tabSpacesEdit);

            std::weak_ptr<App> appWeak(app);
            closeButton->setClickedCallback(
                [appWeak]
                {
                    if (auto app = appWeak.lock())
                    {
                        auto windowOptions = app->getSettingsModel()->getWindowOptions();
                        windowOptions.settings = false;
                        app->getSettingsModel()->setWindowOptions(windowOptions);
                    }
                });

            _fontComboBox->setIndexCallback(
                [appWeak](int index)
                {
                    if (auto app = appWeak.lock())
                    {
                        auto options = app->getSettingsModel()->getTextEditOptions();
                        options.fontInfo.family = getFont(static_cast<Font>(index));
                        app->getSettingsModel()->setTextEditOptions(options);
                    }
                });

            _fontSizeEdit->setCallback(
                [appWeak](int value)
                {
                    if (auto app = appWeak.lock())
                    {
                        auto options = app->getSettingsModel()->getTextEditOptions();
                        options.fontInfo.size = value;
                        app->getSettingsModel()->setTextEditOptions(options);
                    }
                });

            _tabSpacesEdit->setCallback(
                [appWeak](int value)
                {
                    if (auto app = appWeak.lock())
                    {
                        auto options = app->getSettingsModel()->getTextEditModelOptions();
                        options.tabSpaces = value;
                        app->getSettingsModel()->setTextEditModelOptions(options);
                    }
                });

            _textEditOptionsObserver = ValueObserver<TextEditOptions>::create(
                app->getSettingsModel()->observeTextEditOptions(),
                [this](const TextEditOptions& value)
                {
                    int index = -1;
                    for (int i = 0; i < static_cast<int>(Font::Count); ++i)
                    {
                        if (value.fontInfo.family == getFont(static_cast<Font>(i)))
                        {
                            index = i;
                            break;
                        }
                    }
                    _fontComboBox->setCurrentIndex(index);
                    _fontSizeEdit->setValue(value.fontInfo.size);
                });

            _textEditModelOptionsObserver = ValueObserver<TextEditModelOptions>::create(
                app->getSettingsModel()->observeTextEditModelOptions(),
                [this](const TextEditModelOptions& value)
                {
                    _tabSpacesEdit->setValue(value.tabSpaces);
                });
        }

        SettingsWidget::~SettingsWidget()
        {}

        std::shared_ptr<SettingsWidget> SettingsWidget::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<SettingsWidget>(new SettingsWidget);
            out->_init(context, app, parent);
            return out;
        }

        void SettingsWidget::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            _layout->setGeometry(value);
        }

        void SettingsWidget::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _setSizeHint(_layout->getSizeHint());
        }
    }
}