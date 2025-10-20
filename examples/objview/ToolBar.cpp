// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "ToolBar.h"

#include "Actions.h"
#include "App.h"
#include "Document.h"

#include <ftk/UI/Divider.h>
#include <ftk/UI/ToolBar.h>

#include <ftk/Core/Format.h>

using namespace ftk;

namespace objview
{
    void ToolBar::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<App>& app,
        const std::shared_ptr<Actions>& actions,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "examples::objview::ToolBar", parent);

        // Create the layout.
        _layout = HorizontalLayout::create(context, shared_from_this());
        _layout->setSpacingRole(SizeRole::SpacingSmall);

        // Create the tool bars.
        _createFileToolBar(context, actions);
        Divider::create(context, Orientation::Horizontal, _layout);
        _createWindowToolBar(context, actions);
        Divider::create(context, Orientation::Horizontal, _layout);
        _createViewToolBar(context, actions);
        Divider::create(context, Orientation::Horizontal, _layout);
        _createObjectToolBar(context, app, actions);
    }

    ToolBar::~ToolBar()
    {}

    std::shared_ptr<ToolBar> ToolBar::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<App>& app,
        const std::shared_ptr<Actions>& actions,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<ToolBar>(new ToolBar);
        out->_init(context, app, actions, parent);
        return out;
    }

    void ToolBar::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _layout->setGeometry(value);
    }

    void ToolBar::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        _setSizeHint(_layout->getSizeHint());
    }

    void ToolBar::_createFileToolBar(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<Actions>& actions)
    {
        auto toolBar = ftk::ToolBar::create(context, Orientation::Horizontal, _layout);
        for (const auto& key :
            { "File/Open", "File/Close", "File/CloseAll" })
        {
            toolBar->addAction(actions->getAction(key));
        }
    }

    void ToolBar::_createWindowToolBar(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<Actions>& actions)
    {
        auto toolBar = ftk::ToolBar::create(context, Orientation::Horizontal, _layout);
        for (const auto& key :
            { "Window/FullScreen" })
        {
            toolBar->addAction(actions->getAction(key));
        }
    }

    void ToolBar::_createViewToolBar(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<Actions>& actions)
    {
        auto toolBar = ftk::ToolBar::create(context, Orientation::Horizontal, _layout);
        for (const auto& key :
            { "View/Frame", "View/ZoomIn", "View/ZoomOut" })
        {
            toolBar->addAction(actions->getAction(key));
        }
    }

    void ToolBar::_createObjectToolBar(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<App>& app,
        const std::shared_ptr<Actions>& actions)
    {
        auto toolBar = ftk::ToolBar::create(context, Orientation::Horizontal, _layout);
        _buttons["Object/RotateX"] = ToolButton::create(context);
        _buttons["Object/RotateX"]->setFontRole(FontRole::Mono);
        _buttons["Object/RotateX"]->setTooltip("Object X rotation");
        toolBar->addWidget(_buttons["Object/RotateX"]);
        _buttons["Object/RotateY"] = ToolButton::create(context);
        _buttons["Object/RotateY"]->setFontRole(FontRole::Mono);
        _buttons["Object/RotateY"]->setTooltip("Object Y rotation");
        toolBar->addWidget(_buttons["Object/RotateY"]);
        _buttons["Object/RotateZ"] = ToolButton::create(context);
        _buttons["Object/RotateZ"]->setFontRole(FontRole::Mono);
        _buttons["Object/RotateZ"]->setTooltip("Object Z rotation");
        toolBar->addWidget(_buttons["Object/RotateZ"]);

        // Set the rotation callbacks.
        _buttons["Object/RotateX"]->setClickedCallback(
            [this]
            {
                if (auto doc = std::dynamic_pointer_cast<Document>(_current.lock()))
                {
                    V3F r = doc->getRotation();
                    r.x += 90.F;
                    if (r.x >= 360.F)
                    {
                        r.x = 0.F;
                    }
                    doc->setRotation(r);
                }
            });
        _buttons["Object/RotateY"]->setClickedCallback(
            [this]
            {
                if (auto doc = std::dynamic_pointer_cast<Document>(_current.lock()))
                {
                    V3F r = doc->getRotation();
                    r.y += 90.F;
                    if (r.y >= 360.F)
                    {
                        r.y = 0.F;
                    }
                    doc->setRotation(r);
                }
            });
        _buttons["Object/RotateZ"]->setClickedCallback(
            [this]
            {
                if (auto doc = std::dynamic_pointer_cast<Document>(_current.lock()))
                {
                    V3F r = doc->getRotation();
                    r.z += 90.F;
                    if (r.z >= 360.F)
                    {
                        r.z = 0.F;
                    }
                    doc->setRotation(r);
                }
            });

        // Observe the current document to update the toolbars.
        _currentObserver = ValueObserver<std::shared_ptr<IDocument> >::create(
            app->getDocumentModel()->observeCurrent(),
            [this](const std::shared_ptr<IDocument>& idoc)
            {
                _current = idoc;

                if (auto doc = std::dynamic_pointer_cast<Document>(idoc))
                {
                    _rotationObserver = ValueObserver<V3F>::create(
                        doc->observeRotation(),
                        [this](const V3F& value)
                        {
                            _rotation = value;
                            _rotationUpdate();
                        });
                }
                else
                {
                    _rotation = V3F();
                    _rotationObserver.reset();
                    _rotationUpdate();
                }

                const bool current = idoc.get();
                _buttons["Object/RotateX"]->setEnabled(current);
                _buttons["Object/RotateY"]->setEnabled(current);
                _buttons["Object/RotateZ"]->setEnabled(current);
            });

    }

    void ToolBar::_rotationUpdate()
    {
        _buttons["Object/RotateX"]->setText(
            Format("X: {0}").arg(_rotation.x, -1, 3));
        _buttons["Object/RotateY"]->setText(
            Format("Y: {0}").arg(_rotation.y, -1, 3));
        _buttons["Object/RotateZ"]->setText(
            Format("Z: {0}").arg(_rotation.z, -1, 3));
    }
}
