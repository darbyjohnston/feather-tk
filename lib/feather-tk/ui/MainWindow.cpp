// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/MainWindow.h>

#include <feather-tk/ui/Action.h>
#include <feather-tk/ui/App.h>
#include <feather-tk/ui/Divider.h>
#include <feather-tk/ui/MenuBar.h>
#include <feather-tk/ui/RowLayout.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    struct MainWindow::Private
    {
        std::shared_ptr<MenuBar> menuBar;
        std::map<std::string, std::shared_ptr<Menu> > menus;
        std::vector<float> displayScales = { 1.F, 1.5F, 2.F, 2.5F, 3.F, 3.5F, 4.F };
        std::vector<std::shared_ptr<Action> > displayScaleActions;
        std::map<ColorStyle, std::shared_ptr<Action> > colorStyleActions;
        std::shared_ptr<Action> tooltipsAction;
        std::shared_ptr<Divider> menuBarDivider;
        std::shared_ptr<IWidget> centralWidget;
        std::shared_ptr<VerticalLayout> layout;
        std::shared_ptr<VerticalLayout> centralLayout;

        std::shared_ptr<ValueObserver<float> > displayScaleObserver;
        std::shared_ptr<ValueObserver<ColorStyle> > colorStyleObserver;
        std::shared_ptr<ValueObserver<bool> > tooltipsObserver;
    };

    void MainWindow::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<App>& app,
        const std::string& name,
        const Size2I& size)
    {
        Window::_init(context, app, name, size);
        FEATHER_TK_P();

        p.menuBar = MenuBar::create(context);
        auto fileMenu = Menu::create(context);
        fileMenu->addAction(Action::create(
            "Exit",
            Key::Q,
            static_cast<int>(commandKeyModifier),
            [this]
            {
                if (auto app = getApp())
                {
                    app->exit();
                }
            }));
        p.menuBar->addMenu("File", fileMenu);

        p.menus["Window"] = Menu::create(context);
        p.menus["Window"]->addAction(Action::create(
            "Full Screen",
            Key::U,
            static_cast<int>(commandKeyModifier),
            [this](bool value)
            {
                setFullScreen(value);
            }));

        p.menus["ColorStyle"] = p.menus["Window"]->addSubMenu("Color Style");
        for (auto colorStyle : getColorStyleEnums())
        {
            auto action = Action::create(
                getLabel(colorStyle),
                [this, colorStyle]
                {
                    if (auto app = getApp())
                    {
                        app->setColorStyle(colorStyle);
                    }
                });
            p.colorStyleActions[colorStyle] = action;
            p.menus["ColorStyle"]->addAction(action);
        }

        p.menus["DisplayScale"] = p.menus["Window"]->addSubMenu("Display Scale");
        for (size_t i = 0; i < p.displayScales.size(); ++i)
        {
            const float displayScale = p.displayScales[i];
            auto action = Action::create(
                Format("{0}").arg(displayScale).str(),
                [this, displayScale](bool)
                {
                    if (auto app = getApp())
                    {
                        app->setDisplayScale(displayScale);
                    }
                });
            p.displayScaleActions.push_back(action);
            p.menus["DisplayScale"]->addAction(action);
        }

        p.tooltipsAction = Action::create(
            "Tooltips",
            [this](bool value)
            {
                if (auto app = getApp())
                {
                    app->setTooltipsEnabled(value);
                }
            });
        p.menus["Window"]->addAction(p.tooltipsAction);

        p.menuBar->addMenu("Window", p.menus["Window"]);

        p.menuBarDivider = Divider::create(context, Orientation::Vertical);

        p.layout = VerticalLayout::create(context, shared_from_this());
        p.layout->setSpacingRole(SizeRole::None);
        p.menuBar->setParent(p.layout);
        p.menuBarDivider->setParent(p.layout);
        p.centralLayout = VerticalLayout::create(context, p.layout);
        p.centralLayout->setSpacingRole(SizeRole::None);
        p.centralLayout->setVStretch(Stretch::Expanding);

        p.colorStyleObserver = ValueObserver<ColorStyle>::create(
            app->observeColorStyle(),
            [this](ColorStyle value)
            {
                FEATHER_TK_P();
                for (auto colorStyle : getColorStyleEnums())
                {
                    p.menus["ColorStyle"]->setChecked(
                        p.colorStyleActions[colorStyle],
                        colorStyle == value);
                }
            });

        p.displayScaleObserver = ValueObserver<float>::create(
            app->observeDisplayScale(),
            [this](float value)
            {
                FEATHER_TK_P();
                for (size_t i = 0; i < p.displayScales.size() && i < p.displayScaleActions.size(); ++i)
                {
                    p.menus["DisplayScale"]->setChecked(
                        p.displayScaleActions[i],
                        p.displayScales[i] == value);
                }
            });

        p.tooltipsObserver = ValueObserver<bool>::create(
            app->observeTooltipsEnabled(),
            [this](bool value)
            {
                FEATHER_TK_P();
                p.menus["Window"]->setChecked(p.tooltipsAction, value);
            });
    }

    MainWindow::MainWindow() :
        _p(new Private)
    {}

    MainWindow::~MainWindow()
    {}

    std::shared_ptr<MainWindow> MainWindow::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<App>& app,
        const std::string& name,
        const Size2I& size)
    {
        auto out = std::shared_ptr<MainWindow>(new MainWindow);
        out->_init(context, app, name, size);
        return out;
    }

    const std::shared_ptr<MenuBar>& MainWindow::getMenuBar() const
    {
        return _p->menuBar;
    }

    void MainWindow::setWidget(const std::shared_ptr<IWidget>& value)
    {
        FEATHER_TK_P();
        if (p.centralWidget)
        {
            p.centralWidget->setParent(nullptr);
        }
        p.centralWidget = value;
        if (p.centralWidget)
        {
            p.centralWidget->setParent(p.centralLayout);
        }
    }

    void MainWindow::keyPressEvent(KeyEvent& event)
    {
        FEATHER_TK_P();
        event.accept = p.menuBar->shortcut(event.key, event.modifiers);
    }

    void MainWindow::keyReleaseEvent(KeyEvent& event)
    {
        event.accept = true;
    }
}