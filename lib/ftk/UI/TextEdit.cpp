// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/UI/TextEditPrivate.h>

#include <ftk/UI/ScrollWidget.h>

namespace ftk
{
    bool TextEditOptions::operator == (const TextEditOptions& other) const
    {
        return
            lineNumbers == other.lineNumbers &&
            fontRole == other.fontRole;
    }

    bool TextEditOptions::operator != (const TextEditOptions& other) const
    {
        return !(*this == other);
    }

    struct TextEdit::Private
    {
        std::shared_ptr<ObservableValue<TextEditOptions> > options;
        std::shared_ptr<TextEditModel> model;
        std::shared_ptr<TextEditWidget> widget;
        std::shared_ptr<ScrollWidget> scrollWidget;

        std::shared_ptr<ValueObserver<TextEditPos> > cursorObserver;
    };

    void TextEdit::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<TextEditModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "ftk::TextEdit", parent);
        FTK_P();

        p.options = ObservableValue<TextEditOptions>::create();

        p.model = model;
        if (!p.model)
        {
            p.model = TextEditModel::create();
        }

        p.widget = TextEditWidget::create(context, p.model);

        p.scrollWidget = ScrollWidget::create(context, ScrollType::Both, shared_from_this());
        p.scrollWidget->setWidget(p.widget);

        p.widget->setFocusCallback(
            [this](bool value)
            {
                _p->scrollWidget->setBorderColorRole(
                    value ? ColorRole::KeyFocus : ColorRole::Border);
            });

        p.cursorObserver = ValueObserver<TextEditPos>::create(
            p.model->observeCursor(),
            [this](const TextEditPos&)
            {
                _p->scrollWidget->scrollTo(_p->widget->getCursorBox(true));
            });
    }

    TextEdit::TextEdit() :
        _p(new Private)
    {
    }

    TextEdit::~TextEdit()
    {
    }

    std::shared_ptr<TextEdit> TextEdit::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<TextEditModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<TextEdit>(new TextEdit);
        out->_init(context, model, parent);
        return out;
    }

    const std::vector<std::string>& TextEdit::getText() const
    {
        return _p->widget->getText();
    }

    void TextEdit::setText(const std::vector<std::string>& value)
    {
        _p->widget->setText(value);
    }

    void TextEdit::clearText()
    {
        _p->widget->clearText();
    }

    void TextEdit::setTextCallback(const std::function<void(const std::vector<std::string>&)>& value)
    {
        _p->widget->setTextCallback(value);
    }

    void TextEdit::selectAll()
    {
        _p->widget->selectAll();
    }

    void TextEdit::clearSelection()
    {
        _p->widget->clearSelection();
    }

    const TextEditOptions& TextEdit::getOptions() const
    {
        return _p->options->get();
    }

    std::shared_ptr<IObservableValue<TextEditOptions> > TextEdit::observeOptions() const
    {
        return _p->options;
    }

    void TextEdit::setOptions(const TextEditOptions& value)
    {
        FTK_P();
        p.options->setIfChanged(value);
        p.widget->setOptions(value);
    }

    void TextEdit::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _p->scrollWidget->setGeometry(value);
    }

    void TextEdit::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        _setSizeHint(_p->scrollWidget->getSizeHint());
    }
}
