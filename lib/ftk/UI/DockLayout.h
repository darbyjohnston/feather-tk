// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/IWidget.h>

namespace ftk
{
    //! \name Layouts
    ///@{
        
    //! Base class for dock widgets.
    class IDockWidget : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        IDockWidget();

    public:
        virtual ~IDockWidget();

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        FTK_PRIVATE();
    };
        
    //! Dock layout.
    class DockLayout : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        DockLayout();

    public:
        virtual ~DockLayout();

        //! Create a new layout.
        static std::shared_ptr<DockLayout> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        FTK_PRIVATE();
    };
        
    ///@}
}
