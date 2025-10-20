// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/Splitter.h>

using namespace ftk;

namespace widgets
{
    class Splitters : public ftk::IWidget
    {
    protected:
        void _init(const std::shared_ptr<Context>&);

        Splitters() = default;

    public:
        virtual ~Splitters();

        static std::shared_ptr<Splitters> create(const std::shared_ptr<Context>&);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        std::shared_ptr<ftk::Splitter> _splitter;
    };
}
