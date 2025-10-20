// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/RowLayout.h>
#include <ftk/UI/ToolButton.h>

namespace imageview
{
    class Actions;

    //! Tool bar widget.
    class ToolBar : public ftk::IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<ftk::Context>&,
            const std::shared_ptr<Actions>&,
            const std::shared_ptr<ftk::IWidget>& parent);

        ToolBar() = default;

    public:
        virtual ~ToolBar();

        //! Create a new tool bar.
        static std::shared_ptr<ToolBar> create(
            const std::shared_ptr<ftk::Context>&,
            const std::shared_ptr<Actions>&,
            const std::shared_ptr<ftk::IWidget>& parent = nullptr);

        void setGeometry(const ftk::Box2I&) override;
        void sizeHintEvent(const ftk::SizeHintEvent&) override;

    private:
        std::map<std::string, std::shared_ptr<ftk::ToolButton> > _buttons;
        std::shared_ptr<ftk::HorizontalLayout> _layout;
    };
}
