// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/IWidget.h>

#include <ftk/GL/Mesh.h>
#include <ftk/GL/OffscreenBuffer.h>
#include <ftk/GL/Shader.h>

namespace examples
{
    namespace objview
    {
        class Document;

        //! Object view widget.
        class ObjView : public ftk::IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<Document>&,
                const std::shared_ptr<ftk::IWidget>& parent);

            ObjView() = default;

        public:
            virtual ~ObjView();

            //! Create a new view.
            static std::shared_ptr<ObjView> create(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<Document>&,
                const std::shared_ptr<ftk::IWidget>& parent = nullptr);

            void setGeometry(const ftk::Box2I&) override;
            void sizeHintEvent(const ftk::SizeHintEvent&) override;
            void drawEvent(const ftk::Box2I&, const ftk::DrawEvent&) override;
            void mouseMoveEvent(ftk::MouseMoveEvent&) override;
            void mousePressEvent(ftk::MouseClickEvent&) override;
            void mouseReleaseEvent(ftk::MouseClickEvent&) override;

        private:
            std::shared_ptr<ftk::TriMesh3F> _mesh;
            bool _doRender = true;
            ftk::V2F _rotation;
            std::shared_ptr<ftk::gl::VBO> _vbo;
            std::shared_ptr<ftk::gl::VAO> _vao;
            std::shared_ptr<ftk::gl::Shader> _shader;
            std::shared_ptr<ftk::gl::OffscreenBuffer> _buffer;
        };
    }
}