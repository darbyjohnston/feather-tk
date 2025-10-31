// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <ftk/UI/MenuBar.h>

#include <ftk/UI/IButton.h>

namespace ftk
{
    class MenuBarButton : public IButton
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::string&,
            const std::shared_ptr<IWidget>& parent);

        MenuBarButton();

    public:
        virtual ~MenuBarButton();

        static std::shared_ptr<MenuBarButton> create(
            const std::shared_ptr<Context>&,
            const std::string&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        void setCurrent(bool);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;
        void clipEvent(const Box2I&, bool) override;
        void drawEvent(const Box2I&, const DrawEvent&) override;

    private:
        FTK_PRIVATE();
    };
}