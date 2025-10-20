// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/MainWindow.h>
#include <ftk/UI/ScrollWidget.h>

using namespace ftk;

namespace widgets
{
    class Popups : public ftk::IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<MenuBar>&);

        Popups() = default;

    public:
        virtual ~Popups();

        static std::shared_ptr<Popups> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<MenuBar>&);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        std::shared_ptr<ftk::ScrollWidget> _scrollWidget;
    };
}
