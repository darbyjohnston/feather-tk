// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <ftk/UI/IWidget.h>

#include <ftk/Core/Timer.h>

namespace gfx
{
    class App;

    //! Animated noise widget.
    class NoiseWidget : public ftk::IWidget
    {
    protected:
        void _init(const std::shared_ptr<ftk::Context>&);

        NoiseWidget() = default;

    public:
        virtual ~NoiseWidget();

        //! Create a new widget.
        static std::shared_ptr<NoiseWidget> create(
            const std::shared_ptr<ftk::Context>&);

        void setGeometry(const ftk::Box2I&) override;
        void setVisible(bool) override;
        void drawEvent(const ftk::Box2I&, const ftk::DrawEvent&) override;
 
    private:
        void _render();
        void _tick();

        std::shared_ptr<ftk::Image> _image;
        std::shared_ptr<ftk::Timer> _timer;
        double _noiseZ = 0.0;
    };
}
