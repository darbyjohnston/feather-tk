// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <ftk/UI/ScrollWidget.h>

using namespace ftk;

namespace widgets
{
    class Lists : public ftk::IWidget
    {
    protected:
        void _init(const std::shared_ptr<Context>&);

        Lists() = default;

    public:
        virtual ~Lists();

        static std::shared_ptr<Lists> create(const std::shared_ptr<Context>&);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        std::shared_ptr<ftk::ScrollWidget> _scrollWidget;
    };
}
