// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/RenderUtilTest.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/IRender.h>
#include <feather-tk/core/RenderUtil.h>

#include <iostream>

namespace feather_tk
{
    namespace core_test
    {
        RenderUtilTest::RenderUtilTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::core_test::RenderUtilTest")
        {}

        RenderUtilTest::~RenderUtilTest()
        {}

        std::shared_ptr<RenderUtilTest> RenderUtilTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<RenderUtilTest>(new RenderUtilTest(context));
        }
        
        namespace
        {
            class Render : public IRender
            {
            public:
                virtual ~Render() {}

                static std::shared_ptr<Render> create(
                    const std::shared_ptr<Context>&);

                void begin(
                    const Size2I&,
                    const RenderOptions& = RenderOptions()) override;
                void end() override {}
                Size2I getRenderSize() const override;
                void setRenderSize(const Size2I&) override;
                RenderOptions getRenderOptions() const override;
                Box2I getViewport() const override;
                void setViewport(const Box2I&) override;
                void clearViewport(const Color4F&) override {}
                bool getClipRectEnabled() const override;
                void setClipRectEnabled(bool) override;
                Box2I getClipRect() const override;
                void setClipRect(const Box2I&) override;
                M44F getTransform() const override;
                void setTransform(const M44F&) override;
                void drawRect(
                    const Box2F&,
                    const Color4F&) override {}
                void drawRects(
                    const std::vector<Box2F>& rects,
                    const Color4F&) override {}
                void drawLine(
                    const V2F&,
                    const V2F&,
                    const Color4F&,
                    const LineOptions& = LineOptions()) override {}
                void drawLines(
                    const std::vector<std::pair<V2F, V2F> >&,
                    const Color4F&,
                    const LineOptions& = LineOptions()) override {}
                void drawMesh(
                    const TriMesh2F&,
                    const Color4F& = Color4F(1.F, 1.F, 1.F, 1.F),
                    const V2F& pos = V2F()) override {}
                void drawColorMesh(
                    const TriMesh2F&,
                    const Color4F& = Color4F(1.F, 1.F, 1.F, 1.F),
                    const V2F& pos = V2F()) override {}
                void drawTexture(
                    unsigned int,
                    const Box2I&,
                    const Color4F& = Color4F(1.F, 1.F, 1.F),
                    AlphaBlend = AlphaBlend::Straight) override {}
                void drawText(
                    const std::vector<std::shared_ptr<Glyph> >&,
                    const FontMetrics&,
                    const V2F& position,
                    const Color4F& = Color4F(1.F, 1.F, 1.F, 1.F)) override {}
                void drawImage(
                    const std::shared_ptr<Image>&,
                    const TriMesh2F&,
                    const Color4F& = Color4F(1.F, 1.F, 1.F, 1.F),
                    const ImageOptions& = ImageOptions()) override {}
                void drawImage(
                    const std::shared_ptr<Image>&,
                    const Box2F&,
                    const Color4F& = Color4F(1.F, 1.F, 1.F, 1.F),
                    const ImageOptions& = ImageOptions()) override {}

            private:
                Size2I _renderSize;
                RenderOptions _options;
                Box2I _viewport;
                bool _clipRectEnabled = false;
                Box2I _clipRect;
                M44F _transform;
            };

            std::shared_ptr<Render> Render::create(const std::shared_ptr<Context>& context)
            {
                auto out = std::shared_ptr<Render>(new Render);
                out->_init(context);
                return out;
            }

            void Render::begin(
                const Size2I& size,
                const RenderOptions& options)
            {
                _renderSize = size;
                _options = options;
            }

            Size2I Render::getRenderSize() const
            {
                return _renderSize;
            }

            void Render::setRenderSize(const Size2I& value)
            {
                _renderSize = value;
            }

            RenderOptions Render::getRenderOptions() const
            {
                return _options;
            }

            Box2I Render::getViewport() const
            {
                return _viewport;
            }

            void Render::setViewport(const Box2I& value)
            {
                _viewport = value;
            }

            bool Render::getClipRectEnabled() const
            {
                return _clipRectEnabled;
            }

            void Render::setClipRectEnabled(bool value)
            {
                _clipRectEnabled = value;
            }

            Box2I Render::getClipRect() const
            {
                return _clipRect;
            }

            void Render::setClipRect(const Box2I& value)
            {
                _clipRect = value;
            }

            M44F Render::getTransform() const
            {
                return _transform;
            }

            void Render::setTransform(const M44F& value)
            {
                _transform = value;
            }
        }

        void RenderUtilTest::run()
        {
            if (auto context = _context.lock())
            {
                {
                    auto render = Render::create(context);
                    const Size2I a(1280, 960);
                    render->begin(a);
                    {
                        RenderSizeState state(render);
                        const Size2I b(1920, 1080);
                        render->setRenderSize(b);
                        FEATHER_TK_ASSERT(b == render->getRenderSize());
                    }
                    FEATHER_TK_ASSERT(a == render->getRenderSize());
                }
                {
                    auto render = Render::create(context);
                    const Box2I a(0, 0, 1280, 960);
                    render->setViewport(a);
                    {
                        ViewportState state(render);
                        const Box2I b(0, 0, 640, 480);
                        render->setViewport(b);
                        FEATHER_TK_ASSERT(b == render->getViewport());
                    }
                    FEATHER_TK_ASSERT(a == render->getViewport());
                }
                {
                    auto render = Render::create(context);
                    render->setClipRectEnabled(true);
                    {
                        ClipRectEnabledState state(render);
                        render->setClipRectEnabled(false);
                        FEATHER_TK_ASSERT(!render->getClipRectEnabled());
                    }
                    FEATHER_TK_ASSERT(render->getClipRectEnabled());
                }
                {
                    auto render = Render::create(context);
                    const Box2I a(0, 0, 1280, 960);
                    render->setClipRect(a);
                    {
                        ClipRectState state(render);
                        const Box2I b(0, 0, 640, 480);
                        render->setClipRect(b);
                        FEATHER_TK_ASSERT(b == render->getClipRect());
                    }
                    FEATHER_TK_ASSERT(a == render->getClipRect());
                }
                {
                    auto render = Render::create(context);
                    const M44F a = translate(V3F(1.F, 1.F, 1.F));
                    render->setTransform(a);
                    {
                        TransformState state(render);
                        const M44F b = scale(V3F(2.F, 2.F, 2.F));
                        render->setTransform(b);
                        FEATHER_TK_ASSERT(b == render->getTransform());
                    }
                    FEATHER_TK_ASSERT(a == render->getTransform());
                }
            }
        }
    }
}

