// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include "Settings.h"

#include <ftk/UI/IMouseWidget.h>

#include <ftk/GL/Mesh.h>
#include <ftk/GL/OffscreenBuffer.h>
#include <ftk/GL/Shader.h>

namespace objview
{
    class App;
    class Document;
    class HUDWidget;

    //! Object view widget.
    class ObjView : public ftk::IMouseWidget
    {
    protected:
        void _init(
            const std::shared_ptr<ftk::Context>&,
            const std::shared_ptr<App>&,
            const std::shared_ptr<Document>&,
            const std::shared_ptr<ftk::IWidget>& parent);

        ObjView() = default;

    public:
        virtual ~ObjView();

        //! Create a new view.
        static std::shared_ptr<ObjView> create(
            const std::shared_ptr<ftk::Context>&,
            const std::shared_ptr<App>&,
            const std::shared_ptr<Document>&,
            const std::shared_ptr<ftk::IWidget>& parent = nullptr);

        //! \name View
        ///@{

        void setOrbit(const ftk::V2F&);
        void frame();
        void zoomIn();
        void zoomOut();

        void orbitLeft();
        void orbitRight();
        void orbitUp();
        void orbitDown();

        ///@}

        void setGeometry(const ftk::Box2I&) override;
        void sizeHintEvent(const ftk::SizeHintEvent&) override;
        void drawEvent(const ftk::Box2I&, const ftk::DrawEvent&) override;
        void mouseMoveEvent(ftk::MouseMoveEvent&) override;

    private:
        std::shared_ptr<ftk::TriMesh3F> _mesh;
        ftk::Box3F _bbox;
        float _fov = 60.F;
        ftk::V3F _rotation;
        ftk::V3F _position;
        ftk::V2F _orbit;
        float _distance = 10.F;
        RenderSettings _settings;

        bool _doRender = true;
        std::shared_ptr<ftk::gl::VBO> _vbo;
        std::shared_ptr<ftk::gl::VAO> _vao;
        std::shared_ptr<ftk::gl::Shader> _shader;
        std::shared_ptr<ftk::gl::OffscreenBuffer> _buffer;

        std::shared_ptr<HUDWidget> _hudWidget;

        std::shared_ptr<ftk::ValueObserver<ftk::V3F> > _rotationObserver;
        std::shared_ptr<ftk::ValueObserver<RenderSettings> > _renderSettingsObserver;
    };
}
