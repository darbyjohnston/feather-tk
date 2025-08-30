// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "Window.h"

#include "App.h"

#include <ftk/ui/Divider.h>
#include <ftk/ui/FileBrowser.h>
#include <ftk/ui/MenuBar.h>
#include <ftk/ui/RowLayout.h>
#include <ftk/ui/ScrollWidget.h>

using namespace ftk;

namespace ftk
{
    namespace examples
    {
        namespace textedit
        {
            void Window::_init(
                const std::shared_ptr<Context>& context,
                const std::shared_ptr<App>& app,
                const std::string& name,
                const Size2I& size)
            {
                MainWindow::_init(context, app, name, size);

                _menus["File"] = Menu::create(context);
                auto appWeak = std::weak_ptr<App>(app);
                _actions["File/Open"] = Action::create(
                    "Open",
                    "FileOpen",
                    Key::O,
                    static_cast<int>(KeyModifier::Control),
                    [this, appWeak]
                    {
                        if (auto context = getContext())
                        {
                            if (auto fileBrowserSystem = context->getSystem<FileBrowserSystem>())
                            {
                                fileBrowserSystem->open(
                                    getWindow(),
                                    [appWeak](const std::filesystem::path& value)
                                    {
                                        if (auto app = appWeak.lock())
                                        {
                                            app->open(value);
                                        }
                                    });
                            }
                        }
                    });
                _menus["File"]->addAction(_actions["File/Open"]);
                _actions["File/Close"] = Action::create(
                    "Close",
                    "FileClose",
                    Key::E,
                    static_cast<int>(KeyModifier::Control),
                    [this]
                    {
                        _textWidget->setText(std::string());
                    });
                _menus["File"]->addAction(_actions["File/Close"]);
                _menus["File"]->addDivider();
                _actions["File/Exit"] = Action::create(
                    "Exit",
                    Key::Q,
                    static_cast<int>(KeyModifier::Control),
                    [appWeak]
                    {
                        if (auto app = appWeak.lock())
                        {
                            app->exit();
                        }
                    });
                _menus["File"]->addAction(_actions["File/Exit"]);

                _menus["Edit"] = Menu::create(context);
                _menus["Edit/Font"] = _menus["Edit"]->addSubMenu("Font");
                _actions["Edit/Font/Monospace"] = Action::create(
                    "Monospace",
                    [appWeak]
                    {
                        if (auto app = appWeak.lock())
                        {
                            app->setFont(FontRole::Mono);
                        }
                    });
                _menus["Edit/Font"]->addAction(_actions["Edit/Font/Monospace"]);
                _actions["Edit/Font/Regular"] = Action::create(
                    "Regular",
                    [appWeak]
                    {
                        if (auto app = appWeak.lock())
                        {
                            app->setFont(FontRole::Label);
                        }
                    });
                _menus["Edit/Font"]->addAction(_actions["Edit/Font/Regular"]);

                auto menuBar = getMenuBar();
                menuBar->clear();
                menuBar->addMenu("File", _menus["File"]);
                menuBar->addMenu("Edit", _menus["Edit"]);

                _textWidget = Label::create(context);
                _textWidget->setMarginRole(SizeRole::MarginInside);
                _textWidget->setVAlign(VAlign::Top);
                auto scrollWidget = ScrollWidget::create(context, ScrollType::Both);
                scrollWidget->setBorder(false);
                scrollWidget->setVStretch(Stretch::Expanding);
                scrollWidget->setWidget(_textWidget);
                setWidget(scrollWidget);

                _fontObserver = ValueObserver<FontRole>::create(
                    app->observeFont(),
                    [this](FontRole value)
                    {
                        _menus["Edit/Font"]->setChecked(
                            _actions["Edit/Font/Monospace"],
                            FontRole::Mono == value);
                        _menus["Edit/Font"]->setChecked(
                            _actions["Edit/Font/Regular"],
                            FontRole::Label == value);
                        _textWidget->setFontRole(value);
                    });

                _textObserver = ValueObserver<std::string>::create(
                    app->observeText(),
                    [this](const std::string& value)
                    {
                        _textWidget->setText(value);
                    });
            }

            Window::~Window()
            {}

            std::shared_ptr<Window> Window::create(
                const std::shared_ptr<Context>& context,
                const std::shared_ptr<App>& app,
                const std::string& name,
                const Size2I& size)
            {
                auto out = std::shared_ptr<Window>(new Window);
                out->_init(context, app, name, size);
                return out;
            }
        }
    }
}
