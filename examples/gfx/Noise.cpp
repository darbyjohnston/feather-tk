// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#include "Noise.h"

#include <ftk/Core/Noise.h>

using namespace ftk;

namespace gfx
{
    void NoiseWidget::_init(const std::shared_ptr<Context>& context)
    {
        IWidget::_init(context, "NoiseWidget", nullptr);

        _timer = Timer::create(context);
        _timer->setRepeating(true);
    }

    NoiseWidget::~NoiseWidget()
    {}

    std::shared_ptr<NoiseWidget> NoiseWidget::create(const std::shared_ptr<Context>& context)
    {
        auto out = std::shared_ptr<NoiseWidget>(new NoiseWidget);
        out->_init(context);
        return out;
    }

    void NoiseWidget::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        const Box2I& g = getGeometry();
        _image = Image::create(g.w() / 2, g.h() / 2, ImageType::L_U8);
        _render();
    }

    void NoiseWidget::setVisible(bool value)
    {
        const bool changed = value != isVisible(false);
        IWidget::setVisible(value);
        if (changed)
        {
            if (value)
            {
                _timer->start(
                    std::chrono::milliseconds(1000 / 24),
                    [this]
                    {
                        _tick();
                    });
            }
            else
            {
                _timer->stop();
            }
        }
    }

    void NoiseWidget::drawEvent(const Box2I& drawRect, const DrawEvent& event)
    {
        if (_image)
        {
            const Box2I& g = getGeometry();
            ImageOptions options;
            options.cache = false;
            event.render->drawImage(
                _image,
                g,
                Color4F(1.F, 1.F, 1.F),
                options);
        }
    }

    void NoiseWidget::_render()
    {
        if (_image)
        {
            const Size2I& size = _image->getSize();
            uint8_t* data = _image->getData();
            Noise noise;
            for (int y = 0; y < size.h; ++y)
            {
                for (int x = 0; x < size.w; ++x)
                {
                    const double n = noise.get(x / 100.0, y / 100.0, _noiseZ / 100.0);
                    data[y * size.w + x] = clamp(n, 0.0, 1.0) * 255;
                }
            }
        }
    }

    void NoiseWidget::_tick()
    {
        _render();
        _noiseZ += 1.0;
        setDrawUpdate();
    }
}
