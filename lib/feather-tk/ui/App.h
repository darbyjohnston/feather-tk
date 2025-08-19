// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/Style.h>

#include <feather-tk/core/CmdLine.h>
#include <feather-tk/core/IApp.h>
#include <feather-tk/core/ObservableList.h>
#include <feather-tk/core/ObservableMap.h>
#include <feather-tk/core/ObservableValue.h>

#include <list>

namespace feather_tk
{
    class FontSystem;
    class IWidget;
    class IconSystem;
    class TickEvent;
    class Window;

    //! Monitor information.
    struct MonitorInfo
    {
        std::string name;
        Size2I      size;
        int         refreshRate = 0;
        float       dDpi = 0.F;
        float       hDpi = 0.F;
        float       vDpi = 0.F;
        Box2I       bounds;

        bool operator == (const MonitorInfo&) const;
        bool operator != (const MonitorInfo&) const;
    };

    //! Color style.
    enum ColorStyle
    {
        Dark,
        Light,
        Custom,

        Count,
        First = Dark
    };
    FEATHER_TK_ENUM(ColorStyle);

    //! Get custom color roles.
    std::map<ColorRole, Color4F> getCustomColorRoles();

    //! Base class for user interface applications.
    class App : public IApp
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::vector<std::string>&,
            const std::string& name,
            const std::string& summary,
            const std::vector<std::shared_ptr<ICmdLineArg> >& = {},
            const std::vector<std::shared_ptr<ICmdLineOption> >& = {});

        App();

    public:
        virtual ~App();

        //! Create a new application.
        static std::shared_ptr<App> create(
            const std::shared_ptr<Context>&,
            int argc, char** argv,
            const std::string& name,
            const std::string& summary,
            const std::vector<std::shared_ptr<ICmdLineArg> >& = {},
            const std::vector<std::shared_ptr<ICmdLineOption> >& = {});

        //! Create a new application.
        static std::shared_ptr<App> create(
            const std::shared_ptr<Context>&,
            int argc, wchar_t* argv[],
            const std::string& name,
            const std::string& summary,
            const std::vector<std::shared_ptr<ICmdLineArg> >& = {},
            const std::vector<std::shared_ptr<ICmdLineOption> >& = {});

        //! Create a new application.
        static std::shared_ptr<App> create(
            const std::shared_ptr<Context>&,
            const std::vector<std::string>&,
            const std::string& name,
            const std::string& summary,
            const std::vector<std::shared_ptr<ICmdLineArg> >& = {},
            const std::vector<std::shared_ptr<ICmdLineOption> >& = {});

        //! Add a window.
        void addWindow(const std::shared_ptr<Window>&);

        //! Remove a window.
        void removeWindow(const std::shared_ptr<Window>&);

        //! Get the windows.
        const std::list<std::shared_ptr<Window> >& getWindows() const;

        //! Observe the monitors.
        std::shared_ptr<IObservableList<MonitorInfo> > observeMonitors() const;

        //! Get the font system.
        const std::shared_ptr<FontSystem>& getFontSystem() const;

        //! Get the icon system.
        const std::shared_ptr<IconSystem>& getIconSystem() const;

        //! Get the style.
        const std::shared_ptr<Style>& getStyle() const;

        //! Get the color style.
        ColorStyle getColorStyle() const;

        //! Observe the color style.
        std::shared_ptr<IObservableValue<ColorStyle> > observeColorStyle() const;

        //! Set the color style.
        void setColorStyle(ColorStyle);

        //! Get the custom color roles.
        const std::map<ColorRole, Color4F>& getCustomColorRoles() const;

        //! Observe the custom color roles.
        std::shared_ptr<IObservableMap<ColorRole, Color4F> > observeCustomColorRoles() const;

        //! Set the custom color roles.
        void setCustomColorRoles(const std::map<ColorRole, Color4F>&);

        //! Get the color style command line option.
        const std::shared_ptr<CmdLineValueOption<ColorStyle> >& getColorStyleCmdLineOption() const;

        //! Get the default display scale.
        float getDefaultDisplayScale() const;

        //! Get the display scale.
        float getDisplayScale() const;

        //! Observe the display scale.
        std::shared_ptr<IObservableValue<float> > observeDisplayScale() const;

        //! Set the display scale.
        void setDisplayScale(float);

        //! Get the display scale command line option.
        const std::shared_ptr<CmdLineValueOption<float> >& getDisplayScaleCmdLineOption() const;

        //! Get whether tooltips are enabled.
        bool areTooltipsEnabled() const;

        //! Observe whether tooltips are enabled.
        std::shared_ptr<IObservableValue<bool> > observeTooltipsEnabled() const;

        //! Set whether tooltips are enabled.
        void setTooltipsEnabled(bool);

        //! Exit the application.
        void exit();

        //! Tick the event loop.
        void tick();

        void run() override;

    protected:
        virtual void _tick() {}

    private:
        void _tickRecursive(
            const std::shared_ptr<IWidget>&,
            bool visible,
            bool enabled,
            const TickEvent&);

        void _monitorsUpdate();
        void _styleUpdate();

        void _log();

        FEATHER_TK_PRIVATE();
    };
}
