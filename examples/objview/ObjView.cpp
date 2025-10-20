// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "ObjView.h"

#include "App.h"
#include "Document.h"
#include "HUDWidget.h"

#include <ftk/GL/GL.h>

#include <ftk/Core/Error.h>
#include <ftk/Core/Matrix.h>
#include <ftk/Core/RenderUtil.h>
#include <ftk/Core/String.h>

using namespace ftk;

namespace examples
{
    namespace objview
    {
        namespace
        {
            const float mouseMult = .25F;
        }

        FTK_ENUM_IMPL(
            RenderMode,
            "Shaded",
            "Flat",
            "Texture",
            "Normals");

        void ObjView::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<Document>& doc,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "examples::objview::ObjView", parent);

            _setMouseHoverEnabled(true);
            _setMousePressEnabled(true);

            _mesh = doc->getMesh();
            if (_mesh)
            {
                _bbox = bbox(*_mesh);
            }

            _renderMode = ObservableValue<RenderMode>::create(RenderMode::Shaded);

            _hudWidget = HUDWidget::create(context, doc, shared_from_this());

            _animTimer = Timer::create(context);
            _animTimer->setRepeating(true);

            frame();

            _rotationObserver = ValueObserver<V3F>::create(
                doc->observeRotation(),
                [this](const V3F& value)
                {
                    _rotation = value;
                    _doRender = true;
                    _setDrawUpdate();
                });

            _animSettingsObserver = ValueObserver<AnimSettings>::create(
                app->getSettingsModel()->observeAnim(),
                [this](const AnimSettings& value)
                {
                    _anim = value;
                    if (!_anim.enabled)
                    {
                        _animTimer->stop();
                    }
                });
        }

        ObjView::~ObjView()
        {}

        std::shared_ptr<ObjView> ObjView::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<Document>& doc,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<ObjView>(new ObjView);
            out->_init(context, app, doc, parent);
            return out;
        }

        void ObjView::setOrbit(const V2F& value)
        {
            V2F tmp;
            tmp.x = value.x;
            while (tmp.x >= 360.F)
            {
                tmp.x -= 360.F;
            }
            while (tmp.x < 0.F)
            {
                tmp.x += 360.F;
            }
            tmp.y = clamp(value.y, -89.F, 89.F);
            if (tmp == _orbit)
                return;
            _orbit = tmp;
            _doRender = true;
            _setDrawUpdate();
        }

        void ObjView::frame()
        {
            _position = -center(_bbox);
            const float l = std::max(std::max(_bbox.w(), _bbox.h()), _bbox.d()) * 1.5F;
            const float t = tan(deg2rad(_fov / 2.F));
            _distance = t > 0.F ? (l / 2.F) / t : 0.F;
            _doRender = true;
            _setDrawUpdate();
        }

        void ObjView::zoomIn()
        {
            _distance *= .5F;
            _doRender = true;
            _setDrawUpdate();
        }

        void ObjView::zoomOut()
        {
            _distance *= 1.5F;
            _doRender = true;
            _setDrawUpdate();
        }

        void ObjView::orbitLeft()
        {
            setOrbit(_orbit + V2F(10.F, 0.F));
        }

        void ObjView::orbitRight()
        {
            setOrbit(_orbit + V2F(-10.F, 0.F));
        }

        void ObjView::orbitUp()
        {
            setOrbit(_orbit + V2F(0.F, 10.F));
        }

        void ObjView::orbitDown()
        {
            setOrbit(_orbit + V2F(0.F, -10.F));
        }

        RenderMode ObjView::getRenderMode() const
        {
            return _renderMode->get();
        }

        std::shared_ptr<ftk::IObservableValue<RenderMode> > ObjView::observeRenderMode() const
        {
            return _renderMode;
        }

        void ObjView::setRenderMode(RenderMode value)
        {
            if (_renderMode->setIfChanged(value))
            {
                _doRender = true;
                _setDrawUpdate();
            }
        }

        void ObjView::setGeometry(const ftk::Box2I& value)
        {
            const bool changed = value != getGeometry();
            IWidget::setGeometry(value);
            _doRender |= changed;
            _hudWidget->setGeometry(value);
        }

        void ObjView::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _dragLength = event.style->getSizeRole(SizeRole::DragLength, event.displayScale);
            _setSizeHint(Size2I());
        }

        std::string vertexSource()
        {
            return
                "#version 410\n"
                "\n"
                "layout(location = 0) in vec3 vPos;\n"
                "layout(location = 1) in vec2 vTex;\n"
                "layout(location = 2) in vec3 vNorm;\n"
                "layout(location = 3) in vec4 vColor;\n"
                "out vec2 fTex;\n"
                "out vec3 fNorm;\n"
                "out vec4 fColor;\n"
                "\n"
                "struct Transform\n"
                "{\n"
                "    mat4 m;\n"
                "    mat4 mvp;\n"
                "};\n"
                "\n"
                "uniform Transform transform;\n"
                "\n"
                "void main()\n"
                "{\n"
                "    gl_Position = vec4(vPos, 1.0) * transform.mvp;\n"
                "    fTex = vTex;\n"
                "    fNorm = vNorm;\n"
                //"    fNorm = mat3(transpose(inverse(transform.m))) * vNorm;\n"
                "    fColor = vColor;\n"
                "}\n";
        }

        std::string meshFragmentSource()
        {
            return
                "#version 410\n"
                "\n"
                "in vec2 fTex;\n"
                "in vec3 fNorm;\n"
                "in vec4 fColor;\n"
                "out vec4 outColor;\n"
                "\n"
                "// enum RenderMode\n"
                "const uint RenderMode_Shaded  = 0;\n"
                "const uint RenderMode_Flat    = 1;\n"
                "const uint RenderMode_Texture = 2;\n"
                "const uint RenderMode_Normals = 3;\n"
                "\n"
                "uniform int renderMode;\n"
                "uniform vec4 color;\n"
                "\n"
                "void main()\n"
                "{\n"
                "    outColor.r = 0;\n"
                "    outColor.g = 0;\n"
                "    outColor.b = 0;\n"
                "    outColor.a = 0;\n"
                "    if (RenderMode_Shaded == renderMode)\n"
                "    {\n"
                "        vec3 l = normalize(vec3(1, 1, 0));\n"
                "        vec3 n = normalize(fNorm);\n"
                "        float d = max(dot(n, l), 0.0);\n"
                "        outColor.r = d * fColor.r * color.r + .2;\n"
                "        outColor.g = d * fColor.g * color.g + .2;\n"
                "        outColor.b = d * fColor.b * color.b + .2;\n"
                "        outColor.a = fColor.a * color.a;\n"
                "    }\n"
                "    else if (RenderMode_Flat == renderMode)\n"
                "    {\n"
                "        outColor = fColor * color;\n"
                "    }\n"
                "    else if (RenderMode_Texture == renderMode)\n"
                "    {\n"
                "        outColor.r = fTex.x;\n"
                "        outColor.g = fTex.y;\n"
                "        outColor.a = 1;\n"
                "    }\n"
                "    else if (RenderMode_Normals == renderMode)\n"
                "    {\n"
                "        outColor.r = fNorm.x;\n"
                "        outColor.g = fNorm.y;\n"
                "        outColor.b = fNorm.z;\n"
                "        outColor.a = 1;\n"
                "    }\n"
                "}\n";
        }

        void ObjView::drawEvent(const Box2I& drawRect, const DrawEvent& event)
        {
            IWidget::drawEvent(drawRect, event);

            const Box2I& g = getGeometry();
            event.render->drawRect(g, Color4F(0.F, 0.F, 0.F));

            try
            {
                if (_mesh && !_mesh->triangles.empty()  && !_vbo && !_vao)
                {
                    _vbo = gl::VBO::create(
                        _mesh->triangles.size() * 3,
                        gl::VBOType::Pos3_F32_UV_F32_Normal_F32_Color_F32);
                    _vbo->copy(gl::convert(*_mesh, _vbo->getType()));
                    _vao = gl::VAO::create(_vbo->getType(), _vbo->getID());
                }

                if (!_shader)
                {
                    _shader = gl::Shader::create(
                        vertexSource(),
                        meshFragmentSource());
                }

                const Size2I size = g.size();
                gl::OffscreenBufferOptions offscreenBufferOptions;
                offscreenBufferOptions.color = ImageType::RGBA_F32;
#if defined(FTK_API_GL_4_1)
                offscreenBufferOptions.depth = gl::OffscreenDepth::_24;
                offscreenBufferOptions.stencil = gl::OffscreenStencil::_8;
#elif defined(FTK_API_GLES_2)
                offscreenBufferOptions.stencil = gl::OffscreenStencil::_8;
#endif // FTK_API_GL_4_1
                if (gl::doCreate(_buffer, size, offscreenBufferOptions))
                {
                    _buffer = gl::OffscreenBuffer::create(size, offscreenBufferOptions);
                }

                if (_doRender && _buffer)
                {
                    _doRender = false;

                    const ViewportState viewportState(event.render);
                    const ClipRectEnabledState clipRectEnabledState(event.render);
                    const ClipRectState clipRectState(event.render);
                    const TransformState transformState(event.render);
                    const RenderSizeState renderSizeState(event.render);

                    gl::OffscreenBufferBinding binding(_buffer);
                    event.render->setRenderSize(size);
                    event.render->setViewport(Box2I(0, 0, g.w(), g.h()));
                    event.render->setClipRectEnabled(false);
                    glClearColor(.1F, .1F, .1F, 1.F);
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    const float aspect = aspectRatio(size);
                    const auto pm = perspective(_fov, aspect, .1F, 10000.F);
                    M44F vm;
                    vm = vm * translate(V3F(0.F, 0.F, -_distance));
                    vm = vm * rotateX(_orbit.y);
                    vm = vm * rotateY(_orbit.x);
                    vm = vm * rotateX(_rotation.x);
                    vm = vm * rotateY(_rotation.y);
                    vm = vm * rotateZ(_rotation.z);
                    vm = vm * translate(_position);

                    _shader->bind();
                    _shader->setUniform("transform.m", vm);
                    _shader->setUniform("transform.mvp", pm * vm);
                    _shader->setUniform("renderMode", static_cast<int>(_renderMode->get()));
                    _shader->setUniform("color", Color4F(1.F, 1.F, 1.F));

                    if (_vao && _vbo)
                    {
                        glEnable(GL_DEPTH_TEST);
                        _vao->bind();
                        _vao->draw(GL_TRIANGLES, 0, _vbo->getSize());
                    }
                }
            }
            catch (const std::exception& e)
            {
                if (auto context = getContext())
                {
                    context->log("OffscreenWidget", e.what(), LogType::Error);
                }
            }

            if (_buffer)
            {
                const unsigned int id = _buffer->getColorID();
                event.render->drawTexture(id, g, true);
            }
        }

        void ObjView::mouseMoveEvent(MouseMoveEvent& event)
        {
            IWidget::mouseMoveEvent(event);
            if (_isMousePressed())
            {
                const V2I d = event.pos - event.prev;
                const V2F v(d.x * mouseMult, d.y * mouseMult);
                setOrbit(_orbit + v);
                _animVel = v.x;
            }
        }

        void ObjView::mousePressEvent(MouseClickEvent& event)
        {
            IWidget::mousePressEvent(event);
            _animVel = 0.F;
            _animTimer->stop();
        }

        void ObjView::mouseReleaseEvent(MouseClickEvent& event)
        {
            IWidget::mouseReleaseEvent(event);
            const int drag = length(event.pos - _getMousePressPos());
            if (_anim.enabled && drag > _dragLength)
            {
                _animTimer->start(
                    std::chrono::milliseconds(1000 / 60),
                    [this]
                    {
                        setOrbit(_orbit + V2F(_animVel, 0.F));
                        _animVel *= .99F;
                        if (std::fabs(_animVel) <= .001F)
                        {
                            _animTimer->stop();
                        }
                    });
            }
        }
    }
}