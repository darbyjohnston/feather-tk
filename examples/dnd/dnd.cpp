// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "dnd.h"

#include <ftk/ui/DrawUtil.h>
#include <ftk/ui/ScrollWidget.h>

#include <ftk/core/Format.h>

namespace ftk
{
    namespace examples
    {
        namespace dnd
        {
            DragAndDropData::DragAndDropData(const std::shared_ptr<DragWidget>& widget) :
                _widget(widget)
            {}

            DragAndDropData::~DragAndDropData()
            {}

            const std::shared_ptr<DragWidget>& DragAndDropData::getWidget() const
            {
                return _widget;
            }

            void DragWidget::_init(
                const std::shared_ptr<Context>& context,
                int number,
                const std::shared_ptr<IWidget>& parent)
            {
                IWidget::_init(context, "ftk::examples::dnd::DragWidget", parent);

                _setMouseHoverEnabled(true);
                _setMousePressEnabled(true);

                _number = number;

                _label = Label::create(context, Format("{0}").arg(number, 4, '0'), shared_from_this());
                _label->setMarginRole(SizeRole::MarginSmall);
                _label->setHAlign(HAlign::Center);
            }

            DragWidget::~DragWidget()
            {}

            std::shared_ptr<DragWidget> DragWidget::create(
                const std::shared_ptr<Context>& context,
                int number,
                const std::shared_ptr<IWidget>& parent)
            {
                auto out = std::shared_ptr<DragWidget>(new DragWidget);
                out->_init(context, number, parent);
                return out;
            }

            void DragWidget::setGeometry(const Box2I& value)
            {
                IWidget::setGeometry(value);
                _label->setGeometry(getGeometry());
            }

            void DragWidget::sizeHintEvent(const SizeHintEvent& event)
            {
                IWidget::sizeHintEvent(event);
                _dragLength = event.style->getSizeRole(SizeRole::DragLength, event.displayScale);
                _setSizeHint(_label->getSizeHint());
            }

            void DragWidget::drawEvent(
                const Box2I& drawRect,
                const DrawEvent& event)
            {
                IWidget::drawEvent(drawRect, event);
                if (_isMouseInside())
                {
                    const Box2I& g = getGeometry();
                    event.render->drawRect(
                        g,
                        event.style->getColorRole(ColorRole::Hover));
                }
            }

            void DragWidget::mouseEnterEvent(MouseEnterEvent& event)
            {
                IWidget::mouseEnterEvent(event);
                _setDrawUpdate();
            }

            void DragWidget::mouseLeaveEvent()
            {
                IWidget::mouseLeaveEvent();
                _setDrawUpdate();
            }

            void DragWidget::mouseMoveEvent(MouseMoveEvent& event)
            {
                IWidget::mouseMoveEvent(event);
                if (_isMousePressed())
                {
                    const float length = ftk::length(event.pos - _getMousePressPos());
                    if (length > _dragLength)
                    {
                        event.dndData = std::make_shared<DragAndDropData>(
                            std::dynamic_pointer_cast<DragWidget>(shared_from_this()));
                        const Box2I& g = getGeometry();
                        const int w = g.w();
                        const int h = g.h();
                        event.dndCursor = Image::create(w, h, ImageType::RGBA_U8);
                        uint8_t* p = event.dndCursor->getData();
                        for (int y = 0; y < h; ++y)
                        {
                            for (int x = 0; x < w; ++x)
                            {
                                p[0] = 255;
                                p[1] = 255;
                                p[2] = 255;
                                p[3] = 63;
                                p += 4;
                            }
                        }
                        event.dndCursorHotspot = _getMousePos() - g.min;
                    }
                }
            }

            void ContainerWidget::_init(
                const std::shared_ptr<Context>& context,
                const std::shared_ptr<IWidget>& parent)
            {
                IWidget::_init(context, "ftk::examples::dnd::ContainerWidget", parent);

                _layout = VerticalLayout::create(context, shared_from_this());
                _layout->setSpacingRole(SizeRole::None);
            }

            ContainerWidget::~ContainerWidget()
            {}

            std::shared_ptr<ContainerWidget> ContainerWidget::create(
                const std::shared_ptr<Context>& context,
                const std::shared_ptr<IWidget>& parent)
            {
                auto out = std::shared_ptr<ContainerWidget>(new ContainerWidget);
                out->_init(context, parent);
                return out;
            }

            void ContainerWidget::addWidget(const std::shared_ptr<DragWidget>& value)
            {
                value->setParent(_layout);
            }

            void ContainerWidget::setGeometry(const Box2I& value)
            {
                IWidget::setGeometry(value);
                _layout->setGeometry(getGeometry());
            }

            void ContainerWidget::sizeHintEvent(const SizeHintEvent& event)
            {
                IWidget::sizeHintEvent(event);
                _handle = event.style->getSizeRole(SizeRole::Handle, event.displayScale);
                _setSizeHint(_layout->getSizeHint());
            }

            void ContainerWidget::drawOverlayEvent(
                const Box2I& drawRect,
                const DrawEvent& event)
            {
                IWidget::drawOverlayEvent(drawRect, event);
                if (_dropTarget != -1)
                {
                    const Box2I g = _getDropGeom(_dropTarget);
                    event.render->drawRect(
                        g,
                        event.style->getColorRole(ColorRole::Checked));
                }
            }

            void ContainerWidget::dragEnterEvent(DragAndDropEvent& event)
            {
                event.accept = true;
                _dropTarget = _getDropIndex(event.pos);
                _setDrawUpdate();
            }

            void ContainerWidget::dragLeaveEvent(DragAndDropEvent& event)
            {
                event.accept = true;
                _dropTarget = -1;
                _setDrawUpdate();
            }

            void ContainerWidget::dragMoveEvent(DragAndDropEvent& event)
            {
                event.accept = true;
                const int dropTarget = _getDropIndex(event.pos);
                if (dropTarget != _dropTarget)
                {
                    _dropTarget = dropTarget;
                    _setDrawUpdate();
                }
            }

            void ContainerWidget::dropEvent(DragAndDropEvent& event)
            {
                if (auto data = std::dynamic_pointer_cast<DragAndDropData>(event.data))
                {
                    event.accept = true;
                    auto widget = data->getWidget();
                    if (widget->getParent().lock() != _layout)
                    {
                        widget->setParent(_layout);
                    }
                    else
                    {
                        const int index = _layout->getChildIndex(widget);
                        if (index < _dropTarget)
                        {
                            --_dropTarget;
                        }
                    }
                    _layout->moveToIndex(widget, _dropTarget);
                    _dropTarget = -1;
                    _setDrawUpdate();
                }
            }

            int ContainerWidget::_getDropIndex(const V2I& pos) const
            {
                int out = 0;
                for (const auto& child : _layout->getChildren())
                {
                    if (pos.y < center(child->getGeometry()).y)
                    {
                        break;
                    }
                    ++out;
                }
                return out;
            }

            Box2I ContainerWidget::_getDropGeom(int index) const
            {
                Box2I out;
                const auto& children = _layout->getChildren();
                int i = 0;
                for (const auto& child : children)
                {
                    if (i == index)
                    {
                        const Box2I& g = child->getGeometry();
                        out = Box2I(g.min.x, g.min.y - _handle / 2, g.w(), _handle);
                        break;
                    }
                    ++i;
                }
                if (i == children.size())
                {
                    const Box2I& g = children.back()->getGeometry();
                    out = Box2I(g.min.x, g.min.y + g.h() - _handle / 2, g.w(), _handle);
                }
                return out;
            }

            void DndWindow::_init(
                const std::shared_ptr<Context>& context,
                const std::shared_ptr<App>& app)
            {
                MainWindow::_init(context, app, "dnd", Size2I(1280, 960));
            }

            DndWindow::~DndWindow()
            {}

            std::shared_ptr<DndWindow> DndWindow::create(
                const std::shared_ptr<Context>& context,
                const std::shared_ptr<App>& app)
            {
                auto out = std::shared_ptr<DndWindow>(new DndWindow);
                out->_init(context, app);
                return out;
            }

            void DndWindow::_drop(const std::vector<std::string>& value)
            {
                for (size_t i = 0; i < value.size(); ++i)
                {
                    std::cout << Format("Drop {0}: {1}").arg(i).arg(value[i]).str() << std::endl;
                }
            }
        }
    }
}

using namespace ftk;

FTK_MAIN()
{
    try
    {
        // Create the context and application.
        auto context = Context::create();
        auto app = App::create(context, argc, argv, "dnd", "Drag and drop example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create a window.
        auto window = examples::dnd::DndWindow::create(context, app);

        // Create a layout.
        auto layout = HorizontalLayout::create(context);
        layout->setSpacingRole(SizeRole::None);
        layout->setStretch(Stretch::Expanding);
        window->setWidget(layout);
        auto scrollWidget0 = ScrollWidget::create(context, ScrollType::Vertical, layout);
        scrollWidget0->setBorder(false);
        scrollWidget0->setStretch(Stretch::Expanding);
        auto scrollWidget1 = ScrollWidget::create(context, ScrollType::Vertical, layout);
        scrollWidget1->setBorder(false);
        scrollWidget1->setStretch(Stretch::Expanding);

        // Create the drag and drop widgets.
        auto dndContainer0 = examples::dnd::ContainerWidget::create(context);
        scrollWidget0->setWidget(dndContainer0);
        auto dndContainer1 = examples::dnd::ContainerWidget::create(context);
        scrollWidget1->setWidget(dndContainer1);
        for (int i = 0; i < 100; ++i)
        {
            dndContainer0->addWidget(examples::dnd::DragWidget::create(context, i));
            dndContainer1->addWidget(examples::dnd::DragWidget::create(context, i));
        }

        // Show the window and run the application.
        window->show();
        app->run();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

