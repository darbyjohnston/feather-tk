// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/Window.h>

#include <feather-tk/ui/IconSystem.h>
#include <feather-tk/ui/Style.h>
#include <feather-tk/ui/Util.h>

#include <feather-tk/gl/GL.h>
#include <feather-tk/gl/OffscreenBuffer.h>
#include <feather-tk/gl/Render.h>
#include <feather-tk/gl/Window.h>
#if defined(FEATHER_TK_API_GLES_2)
#include <feather-tk/gl/Mesh.h>
#include <feather-tk/gl/Shader.h>
#endif // FEATHER_TK_API_GLES_2

#include <feather-tk/core/Context.h>
#include <feather-tk/core/Format.h>
#include <feather-tk/core/LogSystem.h>
#include <feather-tk/core/FontSystem.h>

#include <SDL2/SDL.h>

#include <codecvt>
#include <locale>

namespace feather_tk
{
    namespace
    {
#if defined(_WINDOWS)
        //! \bug https://social.msdn.microsoft.com/Forums/vstudio/en-US/8f40dcd8-c67f-4eba-9134-a19b9178e481/vs-2015-rc-linker-stdcodecvt-error?forum=vcgeneral
        typedef unsigned int feather_tk_char_t;
#else // _WINDOWS
        typedef char32_t feather_tk_char_t;
#endif // _WINDOWS
    }

    struct Window::Private
    {
        std::weak_ptr<Context> context;

        Size2I size;
        Size2I frameBufferSize;
        std::shared_ptr<ObservableValue<bool> > fullScreen;
        std::shared_ptr<ObservableValue<bool> > floatOnTop;
        std::shared_ptr<ObservableValue<ImageType> > bufferType;
        std::shared_ptr<ObservableValue<float> > displayScale;
        bool refresh = true;
        int modifiers = 0;
        std::shared_ptr<gl::Window> window;

        std::shared_ptr<gl::OffscreenBuffer> buffer;
        std::shared_ptr<IRender> render;
#if defined(FEATHER_TK_API_GLES_2)
        std::shared_ptr<gl::Shader> shader;
#endif // FEATHER_TK_API_GLES_2
    };

    void Window::_init(
        const std::shared_ptr<Context>& context,
        const std::string& name,
        const Size2I& size)
    {
        IWindow::_init(context, name, nullptr);
        FEATHER_TK_P();

        p.context = context;

        p.size = size;
        p.fullScreen = ObservableValue<bool>::create(false);
        p.floatOnTop = ObservableValue<bool>::create(false);
        p.bufferType = ObservableValue<ImageType>::create(gl::offscreenColorDefault);
        p.displayScale = ObservableValue<float>::create(1.F);

        p.window = gl::Window::create(
            context,
            name,
            size,
            static_cast<int>(gl::WindowOptions::DoubleBuffer));

        p.render = _createRender(context->getLogSystem());

        _sizeUpdate();

        setVisible(false);
    }

    Window::Window() :
        _p(new Private)
    {}

    Window::~Window()
    {
        FEATHER_TK_P();
        p.window->makeCurrent();
        p.render.reset();
        p.buffer.reset();
    }

    std::shared_ptr<Window> Window::create(
        const std::shared_ptr<Context>& context,
        const std::string& name,
        const Size2I& size)
    {
        auto out = std::shared_ptr<Window>(new Window);
        out->_init(context, name, size);
        return out;
    }

    uint32_t Window::getID() const
    {
        return _p->window->getID();
    }

    const Size2I& Window::getSize() const
    {
        return _p->size;
    }

    void Window::setSize(const Size2I& value)
    {
        FEATHER_TK_P();
        if (value != p.size)
            return;
        p.size = value;
        p.window->setSize(value);
    }

    bool Window::isFullScreen() const
    {
        return _p->window->isFullScreen();
    }

    std::shared_ptr<IObservableValue<bool> > Window::observeFullScreen() const
    {
        return _p->fullScreen;
    }

    void Window::setFullScreen(bool value)
    {
        _p->window->setFullScreen(value);
    }

    int Window::getScreen() const
    {
        return _p->window->getScreen();
    }

    bool Window::isFloatOnTop() const
    {
        return _p->floatOnTop->get();
    }

    std::shared_ptr<IObservableValue<bool> > Window::observeFloatOnTop() const
    {
        return _p->floatOnTop;
    }

    void Window::setFloatOnTop(bool value)
    {
        FEATHER_TK_P();
        if (p.floatOnTop->setIfChanged(value))
        {
            p.window->setFloatOnTop(value);
        }
    }

    const Size2I& Window::getFrameBufferSize() const
    {
        return _p->frameBufferSize;
    }

    ImageType Window::getFrameBufferType() const
    {
        return _p->bufferType->get();
    }

    std::shared_ptr<IObservableValue<ImageType> > Window::observeFrameBufferType() const
    {
        return _p->bufferType;
    }

    void Window::setFrameBufferType(ImageType value)
    {
        if (_p->bufferType->setIfChanged(value))
        {
            _setDrawUpdate();
        }
    }

    float Window::getContentScale() const
    {
        FEATHER_TK_P();
        return p.size.w > 0 ?
            (p.frameBufferSize.w / static_cast<float>(p.size.w)) :
            0.F;
    }

    float Window::getDisplayScale() const
    {
        return _p->displayScale->get();
    }

    std::shared_ptr<IObservableValue<float> > Window::observeDisplayScale() const
    {
        return _p->displayScale;
    }

    void Window::setDisplayScale(float value)
    {
        FEATHER_TK_P();
        if (p.displayScale->setIfChanged(value))
        {
            _setSizeUpdate();
            _setDrawUpdate();
        }
    }

    void Window::setIcons(const std::vector<std::shared_ptr<Image> >& images)
    {
        _p->window->setIcons(images);
    }

    std::shared_ptr<Image> Window::screenshot(const Box2I& rect)
    {
        FEATHER_TK_P();
        std::shared_ptr<Image> out;
        if (p.buffer)
        {
            Box2I rect2 = rect;
            if (!rect.isValid())
            {
                rect2 = Box2I(V2I(), p.buffer->getSize());
            }
            if (rect2.isValid())
            {
                out = Image::create(rect2.w(), rect2.h(), ImageType::RGBA_U8);
                p.window->makeCurrent();
                gl::OffscreenBufferBinding bufferBinding(p.buffer);
                glPixelStorei(GL_PACK_ALIGNMENT, 1);
#if defined(FEATHER_TK_API_GL_4_1)
                glPixelStorei(GL_PACK_SWAP_BYTES, 0);
#endif // FEATHER_TK_API_GL_4_1
                glReadPixels(
                    rect2.x(),
                    rect2.y(),
                    rect2.w(),
                    rect2.h(),
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    out->getData());
            }
        }
        return out;
    }

    void Window::setGeometry(const Box2I& value)
    {
        IWindow::setGeometry(value);
        for (const auto& child : getChildren())
        {
            child->setGeometry(value);
        }
    }

    void Window::setVisible(bool value)
    {
        IWindow::setVisible(value);
        FEATHER_TK_P();
        if (value)
        {
            p.window->show();
        }
        else
        {
            p.window->hide();
        }
    }

    void Window::sizeHintEvent(const SizeHintEvent& event)
    {
        IWindow::sizeHintEvent(event);
        Size2I sizeHint;
        for (const auto& child : getChildren())
        {
            const Size2I& childSizeHint = child->getSizeHint();
            sizeHint.w = std::max(sizeHint.w, childSizeHint.w);
            sizeHint.h = std::max(sizeHint.h, childSizeHint.h);
        }
        _setSizeHint(sizeHint);
    }
    
    void Window::drawEvent(const Box2I& drawRect, const DrawEvent& event)
    {
        IWindow::drawEvent(drawRect, event);
    }

    std::shared_ptr<IRender> Window::_createRender(const std::shared_ptr<LogSystem>& logSystem)
    {
        return gl::Render::create(logSystem);
    }
    
    void Window::_refresh()
    {
        _setDrawUpdate();
        _p->refresh = true;
    }

    void Window::_sizeUpdate()
    {
        FEATHER_TK_P();
        if (SDL_Window* sdlWindow = SDL_GetWindowFromID(p.window->getID()))
        {
            SDL_GetWindowSize(sdlWindow, &p.size.w, &p.size.h);
            SDL_GL_GetDrawableSize(sdlWindow, &p.frameBufferSize.w, &p.frameBufferSize.h);
        }
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void Window::_update(
        const std::shared_ptr<FontSystem>& fontSystem,
        const std::shared_ptr<IconSystem>& iconSystem,
        const std::shared_ptr<Style>& style)
    {
        FEATHER_TK_P();
        const bool sizeUpdate = _hasSizeUpdate(shared_from_this());
        if (sizeUpdate)
        {
            SizeHintEvent sizeHintEvent(
                fontSystem,
                iconSystem,
                p.displayScale->get(),
                style);
            _sizeHintEventRecursive(shared_from_this(), sizeHintEvent);

            setGeometry(Box2I(V2I(), p.frameBufferSize));

            _clipEventRecursive(
                shared_from_this(),
                getGeometry(),
                !isVisible(false));
        }

        const bool drawUpdate = _hasDrawUpdate(shared_from_this());
        if (p.refresh || drawUpdate || sizeUpdate)
        {
            p.window->makeCurrent();

            gl::OffscreenBufferOptions bufferOptions;
            bufferOptions.color = p.bufferType->get();
            if (gl::doCreate(p.buffer, p.frameBufferSize, bufferOptions))
            {
                p.buffer = gl::OffscreenBuffer::create(p.frameBufferSize, bufferOptions);
            }

            if (p.buffer && (drawUpdate || sizeUpdate))
            {
                gl::OffscreenBufferBinding bufferBinding(p.buffer);
                p.render->begin(p.frameBufferSize);
                p.render->setClipRectEnabled(true);
                DrawEvent drawEvent(
                    fontSystem,
                    iconSystem,
                    p.displayScale->get(),
                    style,
                    p.render);
                _drawEventRecursive(
                    shared_from_this(),
                    Box2I(V2I(), p.frameBufferSize),
                    drawEvent);
                p.render->setClipRectEnabled(false);
                p.render->end();
            }

#if defined(FEATHER_TK_API_GL_4_1)
            if (p.buffer)
            {
                glBindFramebuffer(
                    GL_READ_FRAMEBUFFER,
                    p.buffer->getID());
                glBlitFramebuffer(
                    0,
                    0,
                    p.frameBufferSize.w,
                    p.frameBufferSize.h,
                    0,
                    0,
                    p.frameBufferSize.w,
                    p.frameBufferSize.h,
                    GL_COLOR_BUFFER_BIT,
                    GL_LINEAR);
            }
#elif defined(FEATHER_TK_API_GLES_2)
            if (!p.shader)
            {
                try
                {
                    const std::string vertexSource =
                        "precision mediump float;\n"
                        "\n"
                        "attribute vec3 vPos;\n"
                        "attribute vec2 vTexture;\n"
                        "varying vec2 fTexture;\n"
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
                        "    fTexture = vTexture;\n"
                        "}\n";
                    const std::string fragmentSource =
                        "precision mediump float;\n"
                        "\n"
                        "varying vec2 fTexture;\n"
                        "\n"
                        "uniform sampler2D textureSampler;\n"
                        "\n"
                        "void main()\n"
                        "{\n"
                        "    gl_FragColor = texture2D(textureSampler, fTexture);\n"
                        "}\n";
                    p.shader = gl::Shader::create(vertexSource, fragmentSource);
                }
                catch (const std::exception& e)
                {
                    if (auto context = p.context.lock())
                    {
                        context->getSystem<LogSystem>()->print(
                            "feather_tk::Window",
                            Format("Cannot compile shader: {0}").arg(e.what()),
                            LogType::Error);
                    }
                }
            }
            if (p.shader)
            {
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                glDisable(GL_BLEND);
                glDisable(GL_SCISSOR_TEST);

                p.shader->bind();
                p.shader->setUniform(
                    "transform.mvp",
                    ortho(
                        0.F,
                        static_cast<float>(p.frameBufferSize.w),
                        0.F,
                        static_cast<float>(p.frameBufferSize.h),
                        -1.F,
                        1.F));
                p.shader->setUniform("textureSampler", 0);

                glActiveTexture(static_cast<GLenum>(GL_TEXTURE0));
                glBindTexture(GL_TEXTURE_2D, p.buffer->getColorID());

                auto mesh = feather_tk::mesh(Box2I(
                    0,
                    0,
                    p.frameBufferSize.w,
                    p.frameBufferSize.h));
                auto vboData = gl::convert(
                    mesh,
                    gl::VBOType::Pos2_F32_UV_U16,
                    RangeSizeT(0, mesh.triangles.size() - 1));
                auto vbo = gl::VBO::create(mesh.triangles.size() * 3, gl::VBOType::Pos2_F32_UV_U16);
                vbo->copy(vboData);
                auto vao = gl::VAO::create(gl::VBOType::Pos2_F32_UV_U16, vbo->getID());
                vao->bind();
                vao->draw(GL_TRIANGLES, 0, mesh.triangles.size() * 3);
            }
#endif // FEATHER_TK_API_GL_4_1

            p.window->swap();

            p.refresh = false;
        }
    }

    void Window::_makeCurrent()
    {
        _p->window->makeCurrent();
    }

    void Window::_clearCurrent()
    {
        _p->window->clearCurrent();
    }
}
