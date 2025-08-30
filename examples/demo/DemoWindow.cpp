// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "DemoWindow.h"

#include "Buttons.h"
#include "ColorWidgets.h"
#include "Icons.h"
#include "ImageWidgets.h"
#include "Editors.h"
#include "Layouts.h"
#include "Popups.h"
#include "Sliders.h"

#include <ftk/ui/FileBrowser.h>
#include <ftk/ui/GroupBox.h>
#include <ftk/ui/Menu.h>
#include <ftk/ui/MenuBar.h>
#include <ftk/ui/RowLayout.h>
#include <ftk/ui/ScrollWidget.h>

#include <ftk/core/ImageIO.h>

void DemoWindow::_init(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<App>& app)
{
    MainWindow::_init(context, app, "demo", Size2I(1920, 1080));

    auto fileBrowserSystem = context->getSystem<FileBrowserSystem>();
    fileBrowserSystem->setNativeFileDialog(false);

    auto menuBar = getMenuBar();
    if (auto menu = menuBar->getMenu("Window"))
    {
        menu->addDivider();
        auto action = Action::create(
            "Screenshot",
            Key::S,
            static_cast<int>(commandKeyModifier) | static_cast<int>(KeyModifier::Shift),
            [this]
            {
                _screenshot();
            });
        menu->addAction(action);
        _actions["Window/Screenshot"] = action;
    }

    auto layout = VerticalLayout::create(context);
    layout->setMarginRole(SizeRole::Margin);
    auto scrollWidget = ScrollWidget::create(context);
    scrollWidget->setBorder(false);
    scrollWidget->setStretch(Stretch::Expanding);
    scrollWidget->setWidget(layout);
    setWidget(scrollWidget);

    auto hLayout = HorizontalLayout::create(context, layout);
    auto groupBox = GroupBox::create(context, "Buttons", hLayout);
    Buttons::create(context, groupBox);
    groupBox = GroupBox::create(context, "Editors", hLayout);
    Editors::create(context, groupBox);
    groupBox = GroupBox::create(context, "Sliders", hLayout);
    Sliders::create(context, groupBox);
    groupBox = GroupBox::create(context, "Icons", hLayout);
    Icons::create(context, groupBox);

    hLayout = HorizontalLayout::create(context, layout);
    groupBox = GroupBox::create(context, "Layouts", hLayout);
    Layouts::create(context, groupBox);
    groupBox = GroupBox::create(context, "Popups", hLayout);
    Popups::create(context, groupBox);
    groupBox = GroupBox::create(context, "Color Widgets", hLayout);
    ColorWidgets::create(context, groupBox);

    hLayout = HorizontalLayout::create(context, layout);
    groupBox = GroupBox::create(context, "Image Widgets", hLayout);
    ImageWidgets::create(context, groupBox);

    const Size2I iconSize(128, 128);
    auto icon = Image::create(iconSize, ImageType::RGBA_U8);
    for (int y = 0; y < iconSize.h; ++y)
    {
        uint8_t* iconP = icon->getData() + iconSize.w * y * 4;
        for (int x = 0; x < iconSize.w; ++x)
        {
            const float v = y / static_cast<float>(iconSize.h - 1);
            *iconP++ = v * 255;
            *iconP++ = v * 255;
            *iconP++ = v * 255;
            *iconP++ = 255;
        }
    }
    setIcon(icon);
}

DemoWindow::~DemoWindow()
{}

std::shared_ptr<DemoWindow> DemoWindow::create(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<App>& app)
{
    auto out = std::shared_ptr<DemoWindow>(new DemoWindow);
    out->_init(context, app);
    return out;
}

void DemoWindow::_update(
    const std::shared_ptr<FontSystem>& fontSystem,
    const std::shared_ptr<IconSystem>& iconSystem,
    const std::shared_ptr<Style>& style)
{
    MainWindow::_update(fontSystem, iconSystem, style);
    if (_doScreenshot)
    {
        _doScreenshot = false;
        _screenshot(_screenshotPath);
    }
}

void DemoWindow::_screenshot()
{
    if (auto context = getContext())
    {
        auto fileBrowserSystem = context->getSystem<FileBrowserSystem>();
        fileBrowserSystem->open(
            getWindow(),
            [this](const std::filesystem::path& value)
            {
                _screenshotPath = value;
                _doScreenshot = true;
            },
            _screenshotPath.filename().u8string());
    }
}

void DemoWindow::_screenshot(const std::filesystem::path& path)
{
    if (auto context = getContext())
    {
        if (auto image = screenshot())
        {
            auto imageIO = context->getSystem<ImageIO>();
            if (auto write = imageIO->write(path, image->getInfo()))
            {
                write->write(image);
            }
        }
    }
}
