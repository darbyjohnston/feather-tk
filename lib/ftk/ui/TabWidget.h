// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/ui/IWidget.h>

namespace ftk
{
    //! \name Layouts
    ///@{

    //! Tab widget.
    class TabWidget : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        TabWidget();

    public:
        virtual ~TabWidget();

        //! Create a new widget.
        static std::shared_ptr<TabWidget> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Get the tabs.
        const std::vector<std::string>& getTabs() const;

        //! Add a tab.
        void addTab(
            const std::string& name,
            const std::shared_ptr<IWidget>& widget,
            const std::string& tooltip = std::string());

        //! Remove a tab.
        void removeTab(int);

        //! Remove a tab.
        void removeTab(const std::shared_ptr<IWidget>&);

        //! Clear the tabs.
        void clearTabs();

        //! Get the current tab.
        int getCurrentTab() const;

        //! Set the current tab.
        void setCurrentTab(int);

        //! Set the current tab callback.
        void setTabCallback(const std::function<void(int)>&);

        //! Get the current widget.
        std::shared_ptr<IWidget> getCurrentWidget() const;

        //! Set the current widget.
        void setCurrentWidget(const std::shared_ptr<IWidget>&);

        //! Set the current widget callback.
        void setWidgetCallback(const std::function<void(const std::shared_ptr<IWidget>&)>&);

        //! Get whether the tabs are closable.
        bool areTabsClosable() const;

        //! Set whether the tabs are closable.
        void setTabsClosable(bool);

        //! Set the close callback.
        void setTabCloseCallback(const std::function<void(int)>&);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        void _widgetUpdate();

        FTK_PRIVATE();
    };

    ///@}
}