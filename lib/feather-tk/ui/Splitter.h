// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/IWidget.h>

namespace ftk
{
    //! \name Layouts
    ///@{

    //! Splitter widget.
    class Splitter : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            Orientation,
            const std::shared_ptr<IWidget>& parent);

        Splitter();

    public:
        virtual ~Splitter();

        //! Create a new widget.
        static std::shared_ptr<Splitter> create(
            const std::shared_ptr<Context>&,
            Orientation,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Get the split value.
        float getSplit() const;

        //! Set the split value.
        void setSplit(float);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;
        void drawEvent(const Box2I&, const DrawEvent&) override;
        void mouseEnterEvent(MouseEnterEvent&) override;
        void mouseLeaveEvent() override;
        void mouseMoveEvent(MouseMoveEvent&) override;
        void mousePressEvent(MouseClickEvent&) override;
        void mouseReleaseEvent(MouseClickEvent&) override;

    protected:
        void _releaseMouse() override;

    private:
        FTK_PRIVATE();
    };

    ///@}
}