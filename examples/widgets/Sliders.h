// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <ftk/UI/ScrollWidget.h>

using namespace ftk;

namespace widgets
{
    class Sliders : public ftk::IWidget
    {
    protected:
        void _init(const std::shared_ptr<Context>&);

        Sliders() = default;

    public:
        virtual ~Sliders();

        static std::shared_ptr<Sliders> create(const std::shared_ptr<Context>&);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        std::shared_ptr<ftk::ScrollWidget> _scrollWidget;
    };
}
