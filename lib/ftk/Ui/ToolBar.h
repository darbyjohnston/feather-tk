// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/Ui/IWidget.h>

namespace ftk
{
    class Action;

    //! \name Composite Widgets
    ///@{
        
    //! Tool bar.
    class ToolBar : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            Orientation,
            const std::shared_ptr<IWidget>& parent);

        ToolBar();

    public:
        virtual ~ToolBar();

        //! Create a new widget.
        static std::shared_ptr<ToolBar> create(
            const std::shared_ptr<Context>&,
            Orientation = Orientation::Horizontal,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Add an action.
        void addAction(const std::shared_ptr<Action>&);

        //! Add a widget.
        void addWidget(const std::shared_ptr<IWidget>&);

        //! Clear the tool bar.
        void clear();

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        FTK_PRIVATE();
    };
        
    ///@}
}
