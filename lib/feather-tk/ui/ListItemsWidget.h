// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/ButtonGroup.h>
#include <feather-tk/ui/IWidget.h>

namespace feather_tk
{
    //! \name List Widgets
    ///@{

    //! List item.
    struct ListItem
    {
        ListItem() = default;
        explicit ListItem(
            const std::string& text,
            const std::string& tooltip = std::string());

        std::string text;
        std::string tooltip;

        bool operator == (const ListItem&) const;
        bool operator != (const ListItem&) const;
    };

    //! List items widget.
    class ListItemsWidget : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            ButtonGroupType,
            const std::shared_ptr<IWidget>& parent);

        ListItemsWidget();

    public:
        virtual ~ListItemsWidget();

        //! Create a new widget.
        static std::shared_ptr<ListItemsWidget> create(
            const std::shared_ptr<Context>&,
            ButtonGroupType,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Get the items.
        const std::vector<ListItem>& getItems() const;

        //! Set the items.
        void setItems(const std::vector<ListItem>&);

        //! Set the items.
        void setItems(const std::vector<std::string>&);

        //! Get whether an item is checked.
        bool getChecked(int) const;

        //! Set whether an item is checked.
        void setChecked(int, bool);

        //! Set the callback.
        void setCallback(const std::function<void(int, bool)>&);

        //! Get the current item.
        int getCurrent() const;

        //! Observe the current item.
        std::shared_ptr<IObservableValue<int> > observeCurrent() const;

        //! Set the current item.
        void setCurrent(int);

        //! Observe the item to scroll to.
        std::shared_ptr<IObservableValue<int> > observeScrollTo() const;

        //! Get the search.
        const std::string& getSearch() const;

        //! Set the search.
        void setSearch(const std::string&);

        //! Clear the search.
        void clearSearch();

        //! Get an item rectangle.
        Box2I getRect(int) const;

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;
        void keyFocusEvent(bool) override;
        void keyPressEvent(KeyEvent&) override;
        void keyReleaseEvent(KeyEvent&) override;

    private:
        void _itemsUpdate();
        void _currentUpdate();

        FEATHER_TK_PRIVATE();
    };
}
