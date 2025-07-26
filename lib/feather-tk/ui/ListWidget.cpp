// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/ListWidget.h>

#include <feather-tk/ui/ListItemsWidget.h>

#include <feather-tk/ui/ScrollWidget.h>

namespace feather_tk
{
    struct ListWidget::Private
    {
        std::shared_ptr<ListItemsWidget> widget;
        std::shared_ptr<ScrollWidget> scrollWidget;
        std::shared_ptr<ValueObserver<int> > scrollToObserver;
    };

    void ListWidget::_init(
        const std::shared_ptr<Context>& context,
        ButtonGroupType type,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "feather_tk::ListWidget", parent);
        FEATHER_TK_P();

        p.widget = ListItemsWidget::create(context, type);

        p.scrollWidget = ScrollWidget::create(context, ScrollType::Both, shared_from_this());
        p.scrollWidget->setWidget(p.widget);

        p.scrollToObserver = ValueObserver<int>::create(
            p.widget->observeScrollTo(),
            [this](int value)
            {
                if (value >= 0)
                {
                    _scrollUpdate(value);
                }
            });
    }

    ListWidget::ListWidget() :
        _p(new Private)
    {}

    ListWidget::~ListWidget()
    {}

    std::shared_ptr<ListWidget> ListWidget::create(
        const std::shared_ptr<Context>& context,
        ButtonGroupType type,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<ListWidget>(new ListWidget);
        out->_init(context, type, parent);
        return out;
    }

    const std::vector<ListItem>& ListWidget::getItems() const
    {
        return _p->widget->getItems();
    }

    void ListWidget::setItems(const std::vector<ListItem>& value)
    {
        _p->widget->setItems(value);
    }

    void ListWidget::setItems(const std::vector<std::string>& value)
    {
        _p->widget->setItems(value);
    }

    bool ListWidget::getChecked(int index) const
    {
        return _p->widget->getChecked(index);
    }

    void ListWidget::setChecked(int index, bool value)
    {
        _p->widget->setChecked(index, value);
    }

    void ListWidget::setCallback(const std::function<void(int, bool)>& value)
    {
        _p->widget->setCallback(value);
    }

    int ListWidget::getCurrent() const
    {
        return _p->widget->getCurrent();
    }

    void ListWidget::setCurrent(int value)
    {
        _p->widget->setCurrent(value);
    }

    const std::string& ListWidget::getSearch() const
    {
        return _p->widget->getSearch();
    }

    void ListWidget::setSearch(const std::string& value)
    {
        _p->widget->setSearch(value);
    }

    void ListWidget::clearSearch()
    {
        _p->widget->clearSearch();
    }

    void ListWidget::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _p->scrollWidget->setGeometry(value);
    }

    bool ListWidget::hasBorder() const
    {
        return _p->scrollWidget->hasBorder();
    }

    void ListWidget::setBorder(bool value)
    {
        _p->scrollWidget->setBorder(value);
    }

    void ListWidget::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        _setSizeHint(_p->scrollWidget->getSizeHint());
    }

    void ListWidget::_scrollUpdate(int value)
    {
        FEATHER_TK_P();
        const V2I& pos = _p->scrollWidget->getScrollPos();
        const Box2I vp = _p->scrollWidget->getViewport();
        const Box2I r = _p->widget->getRect(value);
        if (r.min.y < pos.y || r.max.y > pos.y + vp.h())
        {
            _p->scrollWidget->scrollTo(r);
        }
    }
}