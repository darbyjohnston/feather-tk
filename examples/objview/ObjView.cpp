// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "ObjView.h"

#include "Document.h"

#include <ftk/GL/GL.h>

#include <ftk/Core/Matrix.h>
#include <ftk/Core/RenderUtil.h>

using namespace ftk;

namespace examples
{
    namespace objview
    {
        void ObjView::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<Document>& doc,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "examples::objview::ObjView", parent);

            _setMouseHoverEnabled(true);
            _setMousePressEnabled(true);

            _mesh = doc->getMesh();
        }

        ObjView::~ObjView()
        {}

        std::shared_ptr<ObjView> ObjView::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<Document>& doc,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<ObjView>(new ObjView);
            out->_init(context, doc, parent);
            return out;
        }

        void ObjView::setGeometry(const ftk::Box2I& value)
        {
            const bool changed = value != getGeometry();
            IWidget::setGeometry(value);
            _doRender = changed;
        }

        void ObjView::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _setSizeHint(Size2I());
        }

        std::string vertexSource()
        {
            return
                "#version 410\n"
                "\n"
                "layout(location = 0) in vec3 vPos;\n"
                "layout(location = 1) in vec4 vColor;\n"
                "out vec4 fColor;\n"
                "\n"
                "struct Transform\n"
                "{\n"
                "    mat4 mvp;\n"
                "};\n"
                "\n"
                "uniform Transform transform;\n"
                "\n"
                "void main()\n"
                "{\n"
                "    gl_Position = vec4(vPos, 1.0) * transform.mvp;\n"
                "    fColor = vColor;\n"
                "}\n";
        }

        std::string meshFragmentSource()
        {
            return
                "#version 410\n"
                "\n"
                "in vec4 fColor;\n"
                "out vec4 outColor;\n"
                "\n"
                "uniform vec4 color;\n"
                "\n"
                "void main()\n"
                "{\n"
                "\n"
                "    outColor = fColor * color;\n"
                "}\n";
        }

        void ObjView::drawEvent(const Box2I& drawRect, const DrawEvent& event)
        {
            IWidget::drawEvent(drawRect, event);

            const Box2I& g = getGeometry();
            event.render->drawRect(g, Color4F(0.F, 0.F, 0.F));

            try
            {
                if (_mesh && !_vbo && !_vao)
                {
                    _vbo = gl::VBO::create(_mesh->triangles.size() * 3, gl::VBOType::Pos3_F32_Color_U8);
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
                    event.render->clearViewport(Color4F(0.F, 0.F, 1.F));

                    const float aspect = aspectRatio(size);
                    const auto pm = perspective(60.F, aspect, .1F, 10000.F);
                    M44F vm;
                    vm = vm * translate(V3F(0.F, 0.F, -10.F));
                    vm = vm * rotateX(_rotation.y);
                    vm = vm * rotateY(_rotation.x);

                    _shader->bind();
                    _shader->setUniform("transform.mvp", pm * vm);
                    _shader->setUniform("color", Color4F(1.F, 1.F, 1.F));

                    if (_vao && _vbo)
                    {
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
                event.render->drawTexture(id, g);
            }
        }

        void ObjView::mouseMoveEvent(MouseMoveEvent& event)
        {
            IWidget::mouseMoveEvent(event);
            if (_isMousePressed())
            {
                V2I d = event.pos - event.prev;
                _rotation.x += d.x;
                _rotation.y += d.y;
                _doRender = true;
                _setDrawUpdate();
            }
        }

        void ObjView::mousePressEvent(MouseClickEvent& event)
        {
            IWidget::mousePressEvent(event);
        }

        void ObjView::mouseReleaseEvent(MouseClickEvent& event)
        {
            IWidget::mouseReleaseEvent(event);
        }
    }
}