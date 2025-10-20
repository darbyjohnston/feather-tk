// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/IWidget.h>

#include <ftk/GL/OffscreenBuffer.h>
#include <ftk/GL/Shader.h>

#include <ftk/Core/Timer.h>

using namespace ftk;

namespace widgets
{
    class Offscreen : public ftk::IWidget
    {
    protected:
        void _init(const std::shared_ptr<Context>&);

        Offscreen() = default;

    public:
        virtual ~Offscreen();

        static std::shared_ptr<Offscreen> create(const std::shared_ptr<Context>&);

        void drawEvent(const Box2I&, const DrawEvent&) override;

    private:
        float _rotation = 0.F;
        std::shared_ptr<Timer> _timer;
        bool _doRender = true;
        std::shared_ptr<gl::Shader> _shader;
        std::shared_ptr<gl::OffscreenBuffer> _buffer;
    };
}
