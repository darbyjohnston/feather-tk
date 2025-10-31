// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#include "StatusBar.h"

#include "App.h"
#include "Document.h"

#include <ftk/Core/Format.h>
#include <ftk/Core/String.h>

using namespace ftk;

namespace textedit
{
    void StatusBar::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<App>& app,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "examples::textedit::StatusBar", parent);

        // Create the lines labels.
        _labels["Lines"] = Label::create(context, "Lines:");
        _labels["Lines2"] = Label::create(context);
        _labels["Lines2"]->setFontRole(FontRole::Mono);

        // Create the cursor labels.
        _labels["Cursor"] = Label::create(context, "Cursor:");
        _labels["Cursor2"] = Label::create(context);
        _labels["Cursor2"]->setFontRole(FontRole::Mono);

        // Layout the widgets.
        _layout = HorizontalLayout::create(context, shared_from_this());
        _layout->setMarginRole(SizeRole::MarginInside);
        _layout->setSpacingRole(SizeRole::SpacingSmall);
        _layout->addSpacer(Stretch::Expanding);
        _labels["Lines"]->setParent(_layout);
        _labels["Lines2"]->setParent(_layout);
        _labels["Cursor"]->setParent(_layout);
        _labels["Cursor2"]->setParent(_layout);

        // Observe the current document and update the widgets.
        std::weak_ptr<App> appWeak(app);
        _currentObserver = ftk::ValueObserver<std::shared_ptr<IDocument> >::create(
            app->getDocumentModel()->observeCurrent(),
            [this, appWeak](const std::shared_ptr<IDocument>& idoc)
            {
                if (auto doc = std::dynamic_pointer_cast<Document>(idoc))
                {
                    _textObserver = ListObserver<std::string>::create(
                        doc->getModel()->observeText(),
                        [this](const std::vector<std::string>& lines)
                        {
                            _labels["Lines2"]->setText(Format("{0}").
                                arg(lines.size()));
                        });
                    _cursorObserver = ValueObserver<TextEditPos>::create(
                        doc->getModel()->observeCursor(),
                        [this](const TextEditPos& value)
                        {
                            _labels["Cursor2"]->setText(Format("{0}, {1}").
                                arg(value.line + 1, 4).
                                arg(value.chr + 1, 2));
                        });
                }
                else
                {
                    _textObserver.reset();
                    _labels["Lines2"]->setText(std::string());
                    _labels["Cursor2"]->setText(std::string());
                }
            });
    }

    StatusBar::~StatusBar()
    {}

    std::shared_ptr<StatusBar> StatusBar::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<App>& app,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<StatusBar>(new StatusBar);
        out->_init(context, app, parent);
        return out;
    }

    void StatusBar::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _layout->setGeometry(value);
    }

    void StatusBar::sizeHintEvent(const SizeHintEvent& event)
    {
        _setSizeHint(_layout->getSizeHint());
    }
}
