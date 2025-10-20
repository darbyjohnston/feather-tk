// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/ScrollWidget.h>

using namespace ftk;

namespace widgets
{
    class MDI : public ftk::IWidget
    {
    protected:
        void _init(const std::shared_ptr<Context>&);

        MDI() = default;

    public:
        virtual ~MDI();

        static std::shared_ptr<MDI> create(const std::shared_ptr<Context>&);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        std::shared_ptr<ftk::ScrollWidget> _scrollWidget;
    };
}
