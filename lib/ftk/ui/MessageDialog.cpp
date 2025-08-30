// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/ui/MessageDialog.h>

#include <ftk/ui/Divider.h>
#include <ftk/ui/Label.h>
#include <ftk/ui/PushButton.h>
#include <ftk/ui/RowLayout.h>

namespace ftk
{
    class MessageDialogWidget : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::string& title,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent);

        MessageDialogWidget();

    public:
        virtual ~MessageDialogWidget();

        static std::shared_ptr<MessageDialogWidget> create(
            const std::shared_ptr<Context>&,
            const std::string& title,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent = nullptr);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

        void setCallback(const std::function<void(void)>&);

    private:
        std::shared_ptr<Label> _titleLabel;
        std::shared_ptr<Label> _label;
        std::shared_ptr<PushButton> _okButton;
        std::shared_ptr<VerticalLayout> _layout;
        std::function<void(void)> _callback;
    };

    void MessageDialogWidget::_init(
        const std::shared_ptr<Context>& context,
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "ftk::MessageDialogWidget", parent);

        _setMouseHoverEnabled(true);
        _setMousePressEnabled(true);

        _titleLabel = Label::create(context, title);
        _titleLabel->setMarginRole(SizeRole::MarginSmall);
        _titleLabel->setBackgroundRole(ColorRole::Button);

        _label = Label::create(context, text);
        _label->setMarginRole(SizeRole::Margin);
        _label->setAlign(HAlign::Center, VAlign::Top);

        _okButton = PushButton::create(context, "OK");

        _layout = VerticalLayout::create(context, shared_from_this());
        _layout->setSpacingRole(SizeRole::None);
        _titleLabel->setParent(_layout);
        Divider::create(context, Orientation::Vertical, _layout);
        _label->setParent(_layout);
        Divider::create(context, Orientation::Vertical, _layout);
        auto hLayout = HorizontalLayout::create(context, _layout);
        hLayout->setMarginRole(SizeRole::MarginSmall);
        hLayout->setSpacingRole(SizeRole::SpacingSmall);
        hLayout->addSpacer(Stretch::Expanding);
        _okButton->setParent(hLayout);

        _okButton->setClickedCallback(
            [this]
            {
                if (_callback)
                {
                    _callback();
                }
            });
    }

    MessageDialogWidget::MessageDialogWidget()
    {}

    MessageDialogWidget::~MessageDialogWidget()
    {}

    std::shared_ptr<MessageDialogWidget> MessageDialogWidget::create(
        const std::shared_ptr<Context>& context,
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<MessageDialogWidget>(new MessageDialogWidget);
        out->_init(context, title, text, parent);
        return out;
    }

    void MessageDialogWidget::setCallback(const std::function<void(void)>& value)
    {
        _callback = value;
    }

    void MessageDialogWidget::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _layout->setGeometry(value);
    }

    void MessageDialogWidget::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        const int sa = event.style->getSizeRole(SizeRole::ScrollArea, event.displayScale);
        Size2I sizeHint = _layout->getSizeHint();
        sizeHint.w = std::max(sizeHint.w, sa);
        _setSizeHint(sizeHint);
    }

    struct MessageDialog::Private
    {
        std::shared_ptr<MessageDialogWidget> widget;

        std::function<void(void)> callback;
    };

    void MessageDialog::_init(
        const std::shared_ptr<Context>& context,
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        IDialog::_init(context, "ftk::MessageDialog", parent);
        FTK_P();

        p.widget = MessageDialogWidget::create(context, title, text, shared_from_this());

        p.widget->setCallback(
            [this]
            {
                if (_p->callback)
                {
                    _p->callback();
                }
            });
    }

    MessageDialog::MessageDialog() :
        _p(new Private)
    {}

    MessageDialog::~MessageDialog()
    {}

    std::shared_ptr<MessageDialog> MessageDialog::create(
        const std::shared_ptr<Context>& context,
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<MessageDialog>(new MessageDialog);
        out->_init(context, title, text, parent);
        return out;
    }

    void MessageDialog::setCallback(const std::function<void(void)>& value)
    {
        _p->callback = value;
    }

}