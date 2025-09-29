// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "TextWidget.h"

#include "Document.h"

#include <feather-tk/core/String.h>

using namespace ftk;

namespace examples
{
    namespace textedit
    {
        void TextWidget::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<Document>& document,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "examples::textedit::TextWidget", parent);

            _document = document;

            _label = Label::create(context);
            _label->setAlign(HAlign::Left, VAlign::Top);
            _label->setMarginRole(SizeRole::MarginSmall);

            _scrollWidget = ScrollWidget::create(context, ScrollType::Both, shared_from_this());
            _scrollWidget->setBorder(false);
            _scrollWidget->setWidget(_label);

            _linesObserver = ListObserver<std::string>::create(
                document->observeLines(),
                [this](const std::vector<std::string>& lines)
                {
                    _label->setText(join(lines, '\n'));
                });
        }

        TextWidget::~TextWidget()
        {}

        std::shared_ptr<TextWidget> TextWidget::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<Document>& document,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<TextWidget>(new TextWidget);
            out->_init(context, document, parent);
            return out;
        }

        ftk::FontRole TextWidget::getFontRole() const
        {
            return _label->getFontRole();
        }

        void TextWidget::setFontRole(ftk::FontRole value)
        {
            _label->setFontRole(value);
        }

        void TextWidget::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            _scrollWidget->setGeometry(value);
        }

        void TextWidget::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _setSizeHint(_scrollWidget->getSizeHint());
        }
    }
}