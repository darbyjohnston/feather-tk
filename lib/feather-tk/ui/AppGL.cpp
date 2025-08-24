// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/App.h>

#include <feather-tk/ui/ClipboardSystem.h>
#include <feather-tk/ui/IconSystem.h>
#include <feather-tk/ui/Init.h>
#include <feather-tk/ui/Util.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/gl/Init.h>

#include <feather-tk/core/Context.h>
#include <feather-tk/core/Error.h>
#include <feather-tk/core/Format.h>
#include <feather-tk/core/LogSystem.h>
#include <feather-tk/core/String.h>
#include <feather-tk/core/Time.h>
#include <feather-tk/core/Timer.h>

#include <SDL2/SDL.h>

#include <algorithm>
#include <iostream>

namespace feather_tk
{
    namespace
    {
        const std::chrono::milliseconds timeout(5);
    }

    bool MonitorInfo::operator == (const MonitorInfo& other) const
    {
        return
            name == other.name &&
            size == other.size &&
            refreshRate == other.refreshRate &&
            dDpi == other.dDpi &&
            hDpi == other.hDpi &&
            vDpi == other.vDpi &&
            bounds == other.bounds;
    }

    bool MonitorInfo::operator != (const MonitorInfo& other) const
    {
        return !(*this == other);
    }

    FEATHER_TK_ENUM_IMPL(
        ColorStyle,
        "Dark",
        "Light",
        "Custom");

    std::map<ColorRole, Color4F> getCustomColorRoles()
    {
        std::map<ColorRole, Color4F> out = getDefaultColorRoles();
        out[ColorRole::Window] = Color4F(.15F, .15F, .2F);
        out[ColorRole::Button] = Color4F(.2F, .2F, .3F);
        return out;
    }

    struct App::Private
    {
        struct CmdLine
        {
            std::shared_ptr<CmdLineFlagOption> exit;
            std::shared_ptr<CmdLineValueOption<float> > displayScale;
            std::shared_ptr<CmdLineValueOption<ColorStyle> > colorStyle;
        };
        CmdLine cmdLine;

        std::shared_ptr<ObservableList<MonitorInfo> > monitors;
        std::shared_ptr<FontSystem> fontSystem;
        std::shared_ptr<IconSystem> iconSystem;
        std::shared_ptr<Style> style;
        std::shared_ptr<ObservableValue<ColorStyle> > colorStyle;
        std::shared_ptr<ObservableMap<ColorRole, Color4F> > customColorRoles;
        float defaultDisplayScale = 1.F;
        std::shared_ptr<ObservableValue<float> > displayScale;
        std::shared_ptr<ObservableValue<bool> > tooltipsEnabled;
        bool running = true;
        std::list<std::shared_ptr<Window> > windows;
        std::weak_ptr<Window> activeWindow;
        std::vector<std::string> dropFiles;
        std::list<int> tickTimes;
        std::shared_ptr<Timer> logTimer;
    };

    void App::_init(
        const std::shared_ptr<Context>& context,
        const std::vector<std::string>& argv,
        const std::string& name,
        const std::string& summary,
        const std::vector<std::shared_ptr<ICmdLineArg> >& cmdLineArgs,
        const std::vector<std::shared_ptr<ICmdLineOption> >& cmdLineOptions)
    {
        FEATHER_TK_P();

        std::vector<std::shared_ptr<ICmdLineOption> > cmdLineOptionsTmp = cmdLineOptions;
        p.cmdLine.exit = CmdLineFlagOption::create(
            { "-exit" },
            "Start the user interface and then exit.",
            "Testing");
        cmdLineOptionsTmp.push_back(p.cmdLine.exit);
        p.cmdLine.displayScale = CmdLineValueOption<float>::create(
            { "-displayScale", "-ds" },
            "Set the display scale.",
            "Style");
        cmdLineOptionsTmp.push_back(p.cmdLine.displayScale);
        p.cmdLine.colorStyle = CmdLineValueOption<ColorStyle>::create(
            { "-colorStyle", "-cs" },
            "Set the color style.",
            "Style",
            std::optional<ColorStyle>(),
            quotes(getColorStyleLabels()));
        cmdLineOptionsTmp.push_back(p.cmdLine.colorStyle);

        IApp::_init(
            context,
            argv,
            name,
            summary,
            cmdLineArgs,
            cmdLineOptionsTmp);
        uiInit(context);
        gl::init(context);

        p.monitors = ObservableList<MonitorInfo>::create();
        p.fontSystem = context->getSystem<FontSystem>();
        p.iconSystem = context->getSystem<IconSystem>();
        p.style = Style::create(context);
        p.colorStyle = ObservableValue<ColorStyle>::create(ColorStyle::Dark);
        if (p.cmdLine.colorStyle->hasValue())
        {
            p.colorStyle->setIfChanged(p.cmdLine.colorStyle->getValue());
        }
        p.customColorRoles = ObservableMap<ColorRole, Color4F>::create(feather_tk::getCustomColorRoles());

        float dDpi = 0.F;
        float hDpi = 0.F;
        float vDpi = 0.F;
        auto logSystem = _context->getSystem<LogSystem>();
        if (0 == SDL_GetDisplayDPI(0, &dDpi, &hDpi, &vDpi))
        {
            logSystem->print(
                "feather_tk::App",
                Format("Display DPI: {0}").arg(hDpi));
            p.defaultDisplayScale = static_cast<int>((hDpi / getBaseDPI()) / .5F) * .5F;
        }
        if (p.cmdLine.displayScale->hasValue())
        {
            p.defaultDisplayScale = p.cmdLine.displayScale->getValue();
        }
        logSystem->print(
            "feather_tk::App",
            Format("Display scale: {0}").arg(p.defaultDisplayScale));
        p.displayScale = ObservableValue<float>::create(p.defaultDisplayScale);

        p.tooltipsEnabled = ObservableValue<bool>::create(true);

        _monitorsUpdate();
        _styleUpdate();

        p.logTimer = Timer::create(context);
        p.logTimer->setRepeating(true);
        auto weak = std::weak_ptr<App>(std::dynamic_pointer_cast<App>(shared_from_this()));
        p.logTimer->start(
            std::chrono::seconds(10),
            [weak]
            {
                if (auto app = weak.lock())
                {
                    app->_log();
                }
            });
    }

    App::App() :
        _p(new Private)
    {}

    App::~App()
    {}

    std::shared_ptr<App> App::create(
        const std::shared_ptr<Context>& context,
        int argc,
        char** argv,
        const std::string& name,
        const std::string& summary,
        const std::vector<std::shared_ptr<ICmdLineArg> >& cmdLineArgs,
        const std::vector<std::shared_ptr<ICmdLineOption> >& cmdLineOptions)
    {
        auto out = std::shared_ptr<App>(new App);
        out->_init(context, convert(argc, argv), name, summary, cmdLineArgs, cmdLineOptions);
        return out;
    }

    std::shared_ptr<App> App::create(
        const std::shared_ptr<Context>& context,
        int argc,
        wchar_t* argv[],
        const std::string& name,
        const std::string& summary,
        const std::vector<std::shared_ptr<ICmdLineArg> >& cmdLineArgs,
        const std::vector<std::shared_ptr<ICmdLineOption> >& cmdLineOptions)
    {
        auto out = std::shared_ptr<App>(new App);
        out->_init(context, convert(argc, argv), name, summary, cmdLineArgs, cmdLineOptions);
        return out;
    }

    std::shared_ptr<App> App::create(
        const std::shared_ptr<Context>& context,
        const std::vector<std::string>& args,
        const std::string& name,
        const std::string& summary,
        const std::vector<std::shared_ptr<ICmdLineArg> >& cmdLineArgs,
        const std::vector<std::shared_ptr<ICmdLineOption> >& cmdLineOptions)
    {
        auto out = std::shared_ptr<App>(new App);
        out->_init(context, args, name, summary, cmdLineArgs, cmdLineOptions);
        return out;
    }

    void App::addWindow(const std::shared_ptr<Window>& window)
    {
        FEATHER_TK_P();
        const auto i = std::find(p.windows.begin(), p.windows.end(), window);
        if (i == p.windows.end())
        {
            window->setDisplayScale(p.displayScale->get());
            window->setTooltipsEnabled(p.tooltipsEnabled->get());
            p.windows.push_back(window);
        }
    }

    void App::removeWindow(const std::shared_ptr<Window>& window)
    {
        FEATHER_TK_P();
        const auto i = std::find(p.windows.begin(), p.windows.end(), window);
        if (i != p.windows.end())
        {
            p.windows.erase(i);
        }
    }

    const std::list<std::shared_ptr<Window> >& App::getWindows() const
    {
        return _p->windows;
    }

    std::shared_ptr<IObservableList<MonitorInfo> > App::observeMonitors() const
    {
        return _p->monitors;
    }

    const std::shared_ptr<FontSystem>& App::getFontSystem() const
    {
        return _p->fontSystem;
    }

    const std::shared_ptr<IconSystem>& App::getIconSystem() const
    {
        return _p->iconSystem;
    }

    const std::shared_ptr<Style>& App::getStyle() const
    {
        return _p->style;
    }

    ColorStyle App::getColorStyle() const
    {
        return _p->colorStyle->get();
    }

    std::shared_ptr<IObservableValue<ColorStyle> > App::observeColorStyle() const
    {
        return _p->colorStyle;
    }

    void App::setColorStyle(ColorStyle value)
    {
        FEATHER_TK_P();
        if (p.colorStyle->setIfChanged(value))
        {
            _styleUpdate();
        }
    }

    const std::map<ColorRole, Color4F>& App::getCustomColorRoles() const
    {
        return _p->customColorRoles->get();
    }

    std::shared_ptr<IObservableMap<ColorRole, Color4F> > App::observeCustomColorRoles() const
    {
        return _p->customColorRoles;
    }

    void App::setCustomColorRoles(const std::map<ColorRole, Color4F>& value)
    {
        FEATHER_TK_P();
        if (p.customColorRoles->setIfChanged(value))
        {
            if (ColorStyle::Custom == p.colorStyle->get())
            {
                _styleUpdate();
            }
        }
    }

    const std::shared_ptr<CmdLineValueOption<ColorStyle> >& App::getColorStyleCmdLineOption() const
    {
        return _p->cmdLine.colorStyle;
    }

    float App::getDefaultDisplayScale() const
    {
        return _p->defaultDisplayScale;
    }

    float App::getDisplayScale() const
    {
        return _p->displayScale->get();
    }

    std::shared_ptr<IObservableValue<float> > App::observeDisplayScale() const
    {
        return _p->displayScale;
    }

    void App::setDisplayScale(float value)
    {
        FEATHER_TK_P();
        p.displayScale->setIfChanged(value);
        for (const auto& window : p.windows)
        {
            window->setDisplayScale(value);
        }
    }

    const std::shared_ptr<CmdLineValueOption<float> >& App::getDisplayScaleCmdLineOption() const
    {
        return _p->cmdLine.displayScale;
    }

    bool App::areTooltipsEnabled() const
    {
        return _p->tooltipsEnabled->get();
    }

    std::shared_ptr<IObservableValue<bool> > App::observeTooltipsEnabled() const
    {
        return _p->tooltipsEnabled;
    }

    void App::setTooltipsEnabled(bool value)
    {
        FEATHER_TK_P();
        p.tooltipsEnabled->setIfChanged(value);
        for (const auto& window : p.windows)
        {
            window->setTooltipsEnabled(value);
        }
    }

    void App::exit()
    {
        _p->running = false;
    }

    void App::tick()
    {
        FEATHER_TK_P();

        _context->tick();
        _tick();

        for (const auto& window : p.windows)
        {
            TickEvent tickEvent;
            _tickRecursive(
                window,
                window->isVisible(false),
                window->isEnabled(false),
                tickEvent);

            if (window->isVisible(false))
            {
                window->_update(p.fontSystem, p.iconSystem, p.style);
            }
        }
    }

    namespace
    {
        Key fromSDL(int32_t value)
        {
            Key out = Key::Unknown;
            switch (value)
            {
            case SDLK_RETURN: out = Key::Return; break;
            case SDLK_ESCAPE: out = Key::Escape; break;
            case SDLK_BACKSPACE: out = Key::Backspace; break;
            case SDLK_TAB: out = Key::Tab; break;
            case SDLK_SPACE: out = Key::Space; break;
            case SDLK_EXCLAIM: out = Key::Exclaim; break;
            case SDLK_QUOTEDBL: out = Key::DoubleQuote; break;
            case SDLK_HASH: out = Key::Hash; break;
            case SDLK_PERCENT: out = Key::Percent; break;
            case SDLK_DOLLAR: out = Key::Dollar; break;
            case SDLK_AMPERSAND: out = Key::Ampersand; break;
            case SDLK_QUOTE: out = Key::DoubleQuote; break;
            case SDLK_LEFTPAREN: out = Key::LeftParen; break;
            case SDLK_RIGHTPAREN: out = Key::RightParen; break;
            case SDLK_ASTERISK: out = Key::Asterisk; break;
            case SDLK_PLUS: out = Key::Plus; break;
            case SDLK_COMMA: out = Key::Comma; break;
            case SDLK_MINUS: out = Key::Minus; break;
            case SDLK_PERIOD: out = Key::Period; break;
            case SDLK_SLASH: out = Key::Slash; break;
            case SDLK_0: out = Key::_0; break;
            case SDLK_1: out = Key::_1; break;
            case SDLK_2: out = Key::_2; break;
            case SDLK_3: out = Key::_3; break;
            case SDLK_4: out = Key::_4; break;
            case SDLK_5: out = Key::_5; break;
            case SDLK_6: out = Key::_6; break;
            case SDLK_7: out = Key::_7; break;
            case SDLK_8: out = Key::_8; break;
            case SDLK_9: out = Key::_9; break;
            case SDLK_COLON: out = Key::Colon; break;
            case SDLK_SEMICOLON: out = Key::Semicolon; break;
            case SDLK_LESS: out = Key::Less; break;
            case SDLK_EQUALS: out = Key::Equals; break;
            case SDLK_GREATER: out = Key::Greater; break;
            case SDLK_QUESTION: out = Key::Question; break;
            case SDLK_AT: out = Key::At; break;
            case SDLK_LEFTBRACKET: out = Key::LeftBracket; break;
            case SDLK_BACKSLASH: out = Key::Backslash; break;
            case SDLK_RIGHTBRACKET: out = Key::RightBracket; break;
            case SDLK_CARET: out = Key::Caret; break;
            case SDLK_UNDERSCORE: out = Key::Underscore;  break;
            case SDLK_BACKQUOTE: out = Key::BackQuote; break;
            case SDLK_a: out = Key::A; break;
            case SDLK_b: out = Key::B; break;
            case SDLK_c: out = Key::C; break;
            case SDLK_d: out = Key::D; break;
            case SDLK_e: out = Key::E; break;
            case SDLK_f: out = Key::F; break;
            case SDLK_g: out = Key::G; break;
            case SDLK_h: out = Key::H; break;
            case SDLK_i: out = Key::I; break;
            case SDLK_j: out = Key::J; break;
            case SDLK_k: out = Key::K; break;
            case SDLK_l: out = Key::L; break;
            case SDLK_m: out = Key::M; break;
            case SDLK_n: out = Key::N; break;
            case SDLK_o: out = Key::O; break;
            case SDLK_p: out = Key::P; break;
            case SDLK_q: out = Key::Q; break;
            case SDLK_r: out = Key::R; break;
            case SDLK_s: out = Key::S; break;
            case SDLK_t: out = Key::T; break;
            case SDLK_u: out = Key::U; break;
            case SDLK_v: out = Key::V; break;
            case SDLK_w: out = Key::W; break;
            case SDLK_x: out = Key::X; break;
            case SDLK_y: out = Key::Y; break;
            case SDLK_z: out = Key::Z; break;
            case SDLK_CAPSLOCK: out = Key::CapsLock; break;
            case SDLK_F1: out = Key::F1; break;
            case SDLK_F2: out = Key::F2; break;
            case SDLK_F3: out = Key::F3; break;
            case SDLK_F4: out = Key::F4; break;
            case SDLK_F5: out = Key::F5; break;
            case SDLK_F6: out = Key::F6; break;
            case SDLK_F7: out = Key::F7; break;
            case SDLK_F8: out = Key::F8; break;
            case SDLK_F9: out = Key::F9; break;
            case SDLK_F10: out = Key::F10; break;
            case SDLK_F11: out = Key::F11; break;
            case SDLK_F12: out = Key::F12; break;
            case SDLK_PRINTSCREEN: out = Key::PrintScreen; break;
            case SDLK_SCROLLLOCK: out = Key::ScrollLock; break;
            case SDLK_PAUSE: out = Key::Pause; break;
            case SDLK_INSERT: out = Key::Insert; break;
            case SDLK_HOME: out = Key::Home; break;
            case SDLK_PAGEUP: out = Key::PageUp; break;
            case SDLK_DELETE: out = Key::Delete; break;
            case SDLK_END: out = Key::End; break;
            case SDLK_PAGEDOWN: out = Key::PageDown; break;
            case SDLK_RIGHT: out = Key::Right; break;
            case SDLK_LEFT: out = Key::Left; break;
            case SDLK_DOWN: out = Key::Down; break;
            case SDLK_UP: out = Key::Up; break;
            case SDLK_NUMLOCKCLEAR: out = Key::NumLock; break;
            case SDLK_KP_DIVIDE: Key::KeypadDivide; break;
            case SDLK_KP_MULTIPLY: Key::KeypadMulitply; break;
            case SDLK_KP_MINUS: Key::KeypadMinus; break;
            case SDLK_KP_PLUS: Key::KeypadPlus; break;
            case SDLK_KP_ENTER: Key::KeypadEnter; break;
            case SDLK_KP_1: Key::Keypad_1; break;
            case SDLK_KP_2: Key::Keypad_2; break;
            case SDLK_KP_3: Key::Keypad_3; break;
            case SDLK_KP_4: Key::Keypad_4; break;
            case SDLK_KP_5: Key::Keypad_5; break;
            case SDLK_KP_6: Key::Keypad_6; break;
            case SDLK_KP_7: Key::Keypad_7; break;
            case SDLK_KP_8: Key::Keypad_8; break;
            case SDLK_KP_9: Key::Keypad_9; break;
            case SDLK_KP_0: Key::Keypad_0; break;
            case SDLK_KP_PERIOD: Key::KeypadPeriod; break;
            case SDLK_KP_EQUALS: Key::KeypadEquals; break;
            }
            return out;
        }

        int fromSDL(uint16_t value)
        {
            int out = 0;
            if (value & KMOD_SHIFT)
            {
                out |= static_cast<int>(KeyModifier::Shift);
            }
            if (value & KMOD_CTRL)
            {
                out |= static_cast<int>(KeyModifier::Control);
            }
            if (value & KMOD_ALT)
            {
                out |= static_cast<int>(KeyModifier::Alt);
            }
            if (value & KMOD_GUI)
            {
                out |= static_cast<int>(KeyModifier::Super);
            }
            return out;
        }
    }

    void App::run()
    {
        FEATHER_TK_P();
        auto t0 = std::chrono::steady_clock::now();
        while (p.running && !p.windows.empty())
        {
            auto logSystem = _context->getSystem<LogSystem>();
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_DISPLAYEVENT:
                    logSystem->print("feather_tk::App", "SDL_DISPLAYEVENT");
                    _monitorsUpdate();
                    break;
                case SDL_WINDOWEVENT:
                    switch (event.window.event)
                    {
                    case SDL_WINDOWEVENT_SHOWN:
                        for (const auto& window : p.windows)
                        {
                            if (window->getID() == event.window.windowID)
                            {
                                window->setVisible(true);
                                break;
                            }
                        }
                        break;
                    case SDL_WINDOWEVENT_HIDDEN:
                        for (const auto& window : p.windows)
                        {
                            if (window->getID() == event.window.windowID)
                            {
                                window->setVisible(false);
                                break;
                            }
                        }
                        break;
                    case SDL_WINDOWEVENT_EXPOSED:
                        for (const auto& window : p.windows)
                        {
                            if (window->getID() == event.window.windowID)
                            {
                                window->_refresh();
                                break;
                            }
                        }
                        break;
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        for (const auto& window : p.windows)
                        {
                            if (window->getID() == event.window.windowID)
                            {
                                window->_sizeUpdate();
                                break;
                            }
                        }
                        break;
                    case SDL_WINDOWEVENT_ENTER:
                        for (const auto& window : p.windows)
                        {
                            if (window->getID() == event.window.windowID)
                            {
                                window->_cursorEnter(true);
                                p.activeWindow = window;
                                break;
                            }
                        }
                        break;
                    case SDL_WINDOWEVENT_LEAVE:
                        if (auto window = p.activeWindow.lock())
                        {
                            window->_cursorEnter(false);
                        }
                        p.activeWindow.reset();
                        break;
                    case SDL_WINDOWEVENT_CLOSE:
                        for (const auto& window : p.windows)
                        {
                            if (window->getID() == event.window.windowID)
                            {
                                window->close();
                                break;
                            }
                        }
                        break;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if (auto window = p.activeWindow.lock())
                    {
                        const float contentScale = window->getContentScale();
                        window->_cursorPos(V2I(
                            event.motion.x * contentScale,
                            event.motion.y * contentScale));
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (auto window = p.activeWindow.lock())
                    {
                        window->_mouseButton(
                            event.button.button,
                            true,
                            fromSDL(static_cast<uint16_t>(SDL_GetModState())));
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (auto window = p.activeWindow.lock())
                    {
                        window->_mouseButton(
                            event.button.button,
                            false,
                            fromSDL(static_cast<uint16_t>(SDL_GetModState())));
                    }
                    break;
                case SDL_MOUSEWHEEL:
                    if (auto window = p.activeWindow.lock())
                    {
                        const float contentScale = window->getContentScale();
                        window->_scroll(V2F(
                            event.wheel.preciseX * contentScale,
                            event.wheel.preciseY * contentScale),
                            fromSDL(static_cast<uint16_t>(SDL_GetModState())));
                    }
                    break;

                case SDL_KEYDOWN:
                    if (auto window = p.activeWindow.lock())
                    {
                        window->_key(
                            fromSDL(event.key.keysym.sym),
                            true,
                            fromSDL(event.key.keysym.mod));
                    }
                    break;
                case SDL_KEYUP:
                    if (auto window = p.activeWindow.lock())
                    {
                        window->_key(
                            fromSDL(event.key.keysym.sym),
                            false,
                            fromSDL(event.key.keysym.mod));
                    }
                    break;
                case SDL_TEXTINPUT:
                    if (auto window = p.activeWindow.lock())
                    {
                        window->_text(event.text.text);
                    }
                    break;

                case SDL_CLIPBOARDUPDATE:
                {
                    const std::string text = SDL_GetClipboardText();
                    _context->getSystem<ClipboardSystem>()->setText(text);
                    break;
                }

                case SDL_DROPFILE:
                    logSystem->print("feather_tk::App", Format("SDL_DROPFILE: {0}").arg(event.drop.file));
                    p.dropFiles.push_back(event.drop.file);
                    break;
                case SDL_DROPBEGIN:
                    logSystem->print("feather_tk::App", "SDL_DROPBEGIN");
                    p.dropFiles.clear();
                    break;
                case SDL_DROPCOMPLETE:
                {
                    logSystem->print("feather_tk::App", "SDL_DROPCOMPLETE");
                    bool found = false;
                    for (const auto& window : p.windows)
                    {
                        if (window->getID() == event.drop.windowID)
                        {
                            found = true;
                            window->_drop(p.dropFiles);
                            break;
                        }
                    }
                    if (!found)
                    {
                        if (auto window = p.activeWindow.lock())
                        {
                            window->_drop(p.dropFiles);
                        }
                        else if (!p.windows.empty())
                        {
                            p.windows.front()->_drop(p.dropFiles);
                        }
                    }
                    break;
                }
                default: break;
                }
            }

            tick();

            auto t1 = std::chrono::steady_clock::now();
            sleep(timeout, t0, t1);
            t1 = std::chrono::steady_clock::now();
            const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
            p.tickTimes.push_back(diff.count());
            while (p.tickTimes.size() > 10)
            {
                p.tickTimes.pop_front();
            }
            t0 = t1;

            size_t visibleWindows = 0;
            for (const auto& window : p.windows)
            {
                if (window->isVisible(false))
                {
                    ++visibleWindows;
                }
            }
            if (p.cmdLine.exit->found() || 0 == visibleWindows)
            {
                break;
            }
        }
    }

    void App::_tickRecursive(
        const std::shared_ptr<IWidget>& widget,
        bool visible,
        bool enabled,
        const TickEvent& event)
    {
        FEATHER_TK_P();
        const bool parentsVisible = visible && widget->isVisible(false);
        const bool parentsEnabled = enabled && widget->isEnabled(false);
        for (const auto& child : widget->getChildren())
        {
            _tickRecursive(
                child,
                parentsVisible,
                parentsEnabled,
                event);
        }
        widget->tickEvent(visible, enabled, event);
    }

    void App::_monitorsUpdate()
    {
        FEATHER_TK_P();
        std::vector<MonitorInfo> monitors;
        const int displayCount = SDL_GetNumVideoDisplays();
        for (int i = 0; i < displayCount; ++i)
        {
            MonitorInfo monitor;
            monitor.name = SDL_GetDisplayName(i);
            SDL_DisplayMode sdlDisplayMode;
            SDL_GetCurrentDisplayMode(i, &sdlDisplayMode);
            monitor.size.w = sdlDisplayMode.w;
            monitor.size.h = sdlDisplayMode.h;
            monitor.refreshRate = sdlDisplayMode.refresh_rate;
            SDL_GetDisplayDPI(i, &monitor.dDpi, &monitor.hDpi, &monitor.vDpi);
            SDL_Rect sdlRect;
            SDL_GetDisplayBounds(i, &sdlRect);
            monitor.bounds = Box2I(sdlRect.x, sdlRect.y, sdlRect.w, sdlRect.h);
            monitors.push_back(monitor);
        }
        p.monitors->setIfChanged(monitors);

        std::vector<std::string> lines;
        for (int i = 0; i < monitors.size(); ++i)
        {
            lines.push_back(Format("Monitor: {0}").arg(monitors[i].name));
            lines.push_back(Format("    Size: {0}").arg(monitors[i].size));
            lines.push_back(Format("    Referesh rate: {0}").arg(monitors[i].refreshRate));
            lines.push_back(Format("    DPI: {0}").arg(monitors[i].hDpi));
            lines.push_back(Format("    Bounds: {0}").arg(monitors[i].bounds));
        }
        if (!lines.empty())
        {
            auto logSystem = _context->getSystem<LogSystem>();
            logSystem->print(
                "feather_tk::App",
                join(lines, '\n'));
        }
    }

    void App::_styleUpdate()
    {
        FEATHER_TK_P();
        std::map<ColorRole, Color4F> colorRoles;
        switch (p.colorStyle->get())
        {
        case ColorStyle::Dark: colorRoles = getDefaultColorRoles(); break;
        case ColorStyle::Light: colorRoles = getLightColorRoles(); break;
        case ColorStyle::Custom: colorRoles = p.customColorRoles->get(); break;
        default: break;
        }
        p.style->setColorRoles(colorRoles);
    }

    void App::_log()
    {
        FEATHER_TK_P();
        double tickAverage = 0.0;
        if (!p.tickTimes.empty())
        {
            for (auto t : p.tickTimes)
            {
                tickAverage += t;
            }
            tickAverage /= static_cast<double>(p.tickTimes.size());
        }
        auto logSystem = _context->getSystem<LogSystem>();
        logSystem->print(
            "feather_tk::App",
            Format("Average tick time: {0}ms").arg(tickAverage));
    }
}
