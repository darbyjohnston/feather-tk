// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/IMouseWidget.h>
#include <ftk/UI/Label.h>
#include <ftk/UI/RowLayout.h>
#include <ftk/UI/ScrollWidget.h>

using namespace ftk;

namespace widgets
{
    class DragWidget;

    class DragAndDropData : public ftk::DragAndDropData
    {
    public:
        DragAndDropData(const std::shared_ptr<DragWidget>&);

        virtual ~DragAndDropData();

        const std::shared_ptr<DragWidget>& getWidget() const;

    private:
        std::shared_ptr<DragWidget> _widget;
    };

    class DragWidget : public ftk::IMouseWidget
    {
    protected:
        void _init(
            const std::shared_ptr<ftk::Context>&,
            int,
            const std::shared_ptr<ftk::IWidget>& parent);

        DragWidget() = default;

    public:
        virtual ~DragWidget();

        static std::shared_ptr<DragWidget> create(
            const std::shared_ptr<ftk::Context>&,
            int,
            const std::shared_ptr<ftk::IWidget>& parent = nullptr);

        void setGeometry(const ftk::Box2I&) override;
        void sizeHintEvent(const ftk::SizeHintEvent&) override;
        void drawEvent(const ftk::Box2I&, const ftk::DrawEvent&) override;
        void mouseEnterEvent(ftk::MouseEnterEvent&) override;
        void mouseLeaveEvent() override;
        void mouseMoveEvent(ftk::MouseMoveEvent&) override;

    private:
        std::shared_ptr<ftk::Label> _label;
        int _number = 0;
        int _dragLength = 0;
    };

    class ContainerWidget : public ftk::IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<ftk::Context>&,
            const std::shared_ptr<ftk::IWidget>& parent);

        ContainerWidget() = default;

    public:
        virtual ~ContainerWidget();

        static std::shared_ptr<ContainerWidget> create(
            const std::shared_ptr<ftk::Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        void addWidget(const std::shared_ptr<DragWidget>&);

        void setGeometry(const ftk::Box2I&) override;
        void sizeHintEvent(const ftk::SizeHintEvent&) override;
        void drawOverlayEvent(const ftk::Box2I&, const ftk::DrawEvent&) override;
        void dragEnterEvent(ftk::DragAndDropEvent&) override;
        void dragLeaveEvent(ftk::DragAndDropEvent&) override;
        void dragMoveEvent(ftk::DragAndDropEvent&) override;
        void dropEvent(ftk::DragAndDropEvent&) override;

    private:
        int _getDropIndex(const ftk::V2I&) const;
        ftk::Box2I _getDropGeom(int) const;

        std::shared_ptr<ftk::VerticalLayout> _layout;
        int _handle = 0;
        int _dropTarget = -1;
    };

    class DnD : public ftk::IWidget
    {
    protected:
        void _init(const std::shared_ptr<Context>&);

        DnD() = default;

    public:
        virtual ~DnD();

        static std::shared_ptr<DnD> create(const std::shared_ptr<Context>&);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        std::shared_ptr<ftk::HorizontalLayout> _layout;
    };
}
