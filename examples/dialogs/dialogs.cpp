// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "dialogs.h"

#include <ftk/ui/DialogSystem.h>
#include <ftk/ui/Divider.h>
#include <ftk/ui/FileBrowser.h>
#include <ftk/ui/FileEdit.h>
#include <ftk/ui/MenuBar.h>
#include <ftk/ui/PushButton.h>
#include <ftk/ui/RecentFilesModel.h>
#include <ftk/ui/RowLayout.h>

#include <ftk/core/Format.h>

void DialogsWindow::_init(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<App>& app,
    const std::string& name,
    const Size2I& size)
{
    MainWindow::_init(context, app, name, size);

    // Load the settings.
    _settings = Settings::create(context, getSettingsPath("feather-tk", "dialogs.json"));

    // Create the menus.
    auto menu = getMenuBar()->getMenu("File");
    menu->clear();
    menu->addAction(Action::create(
        "Open",
        Key::O,
        static_cast<int>(commandKeyModifier),
        [this]
        {
            if (auto context = getContext())
            {
                auto fileBrowserSystem = context->getSystem<FileBrowserSystem>();
                fileBrowserSystem->open(
                    getWindow(),
                    [this](const std::filesystem::path& value)
                    {
                        std::cout << value.u8string() << std::endl;
                    });
            }
        }));
    auto action = Action::create(
        "Close",
        Key::E,
        static_cast<int>(commandKeyModifier),
        [] {});
    menu->addAction(action);
    menu->setEnabled(action, false);
    menu->addDivider();
    std::weak_ptr<App> appWeak(app);
    menu->addAction(Action::create(
        "Exit",
        Key::Q,
        static_cast<int>(commandKeyModifier),
        [appWeak]
        {
            if (auto app = appWeak.lock())
            {
                app->exit();
            }
        }));

    // Create the layout.
    auto layout = VerticalLayout::create(context);
    layout->setMarginRole(SizeRole::Margin);
    setWidget(layout);

    // Message dialog.
    auto button = PushButton::create(context, "Message Dialog", layout);
    button->setClickedCallback(
        [this]
        {
            if (auto context = getContext())
            {
                context->getSystem<DialogSystem>()->message(
                    "Message",
                    "Hello world!",
                    std::dynamic_pointer_cast<DialogsWindow>(shared_from_this()));
            }
        });

    // Confirmation dialog.
    button = PushButton::create(context, "Confirmation Dialog", layout);
    button->setClickedCallback(
        [this]
        {
            if (auto context = getContext())
            {
                context->getSystem<DialogSystem>()->confirm(
                    "Confirm",
                    "Hello world?",
                    std::dynamic_pointer_cast<DialogsWindow>(shared_from_this()),
                    [](bool value)
                    {
                        std::cout << "Hello world: " << value << std::endl;
                    });
            }
        });

    // Progress dialog.
    _progressTimer = Timer::create(context);
    _progressTimer->setRepeating(true);
    button = PushButton::create(context, "Progress Dialog", layout);
    button->setClickedCallback(
        [this]
        {
            if (auto context = getContext())
            {
                const double inc = 0.005;
                const double max = 1.0;
                _progressDialog = ProgressDialog::create(
                    context,
                    "Progress",
                    "In progress:");
                _progressDialog->setMessage(Format("{0} / {1}").arg(0).arg(int(max / inc)));
                _progressDialog->setCloseCallback(
                    [this]
                    {
                        _progressTimer->stop();
                        _progressDialog.reset();
                    });
                _progressDialog->open(std::dynamic_pointer_cast<IWindow>(shared_from_this()));
                _progressTimer->start(
                    std::chrono::microseconds(500),
                    [this, max, inc]
                    {
                        double v = _progressDialog->getValue();
                        v += 0.005;
                        if (v < 1.0)
                        {
                            _progressDialog->setValue(v);
                            _progressDialog->setMessage(
                                Format("{0} / {1}").arg(v * (max / inc)).arg(int(max / inc)));
                        }
                        else
                        {
                            _progressDialog->close();
                        }
                    });
            }
        });

    // File browsers.
    FileBrowserOptions fileBrowserOptions;
    _settings->getT("/FileBrowser/Options", fileBrowserOptions);
    auto fileBrowserSystem = context->getSystem<FileBrowserSystem>();
    fileBrowserSystem->getModel()->setOptions(fileBrowserOptions);
    fileBrowserSystem->getModel()->setExtensions({ ".h", ".cpp" });
    std::string extension;
    _settings->get("/FileBrowser/Extension", extension);
    fileBrowserSystem->getModel()->setExtension(extension);

    auto recentFilesModel = RecentFilesModel::create(context);
    size_t recentFilesMax = 10;
    _settings->get("/FileBrowser/RecentFilesMax", recentFilesMax);
    std::vector<std::filesystem::path> recentFiles;
    nlohmann::json json;
    _settings->get("/FileBrowser/RecentFiles", json);
    if (json.is_array())
    {
        for (auto i = json.begin(); i != json.end(); ++i)
        {
            if (i->is_string())
            {
                recentFiles.push_back(std::filesystem::u8path(i->get<std::string>()));
            }
        }
    }
    recentFilesModel->setRecentMax(recentFilesMax);
    recentFilesModel->setRecent(recentFiles);
    fileBrowserSystem->setRecentFilesModel(recentFilesModel);

    auto fileEdit = FileEdit::create(context, layout);
    fileEdit->setPath("File Browser");
    auto dirEdit = FileEdit::create(context, FileBrowserMode::Dir, layout);
    dirEdit->setPath("Directory Browser");
}

DialogsWindow::~DialogsWindow()
{
    auto fileBrowserSystem = getContext()->getSystem<FileBrowserSystem>();
    auto fileBrowserOptions = fileBrowserSystem->getModel()->getOptions();
    _settings->setT("/FileBrowser/Options", fileBrowserOptions);
    _settings->set("/FileBrowser/Extension", fileBrowserSystem->getModel()->getExtension());

    auto recentFilesModel = fileBrowserSystem->getRecentFilesModel();
    _settings->set("/FileBrowser/RecentFilesMax", static_cast<int>(recentFilesModel->getRecentMax()));
    nlohmann::json json;
    for (const auto& path : recentFilesModel->getRecent())
    {
        json.push_back(path.u8string());
    }
    _settings->set("/FileBrowser/RecentFiles", json);
}

std::shared_ptr<Window> DialogsWindow::create(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<App>& app,
    const std::string& name,
    const Size2I& size)
{
    auto out = std::shared_ptr<DialogsWindow>(new DialogsWindow);
    out->_init(context, app, name, size);
    return out;
}

FTK_MAIN()
{
    try
    {
        // Create the context and application.
        auto context = Context::create();
        auto app = App::create(context, argc, argv, "dialogs", "Dialogs example");
        if (app->getExit() != 0)
            return app->getExit();

        // Disable the native file dialog.
        context->getSystem<FileBrowserSystem>()->setNativeFileDialog(false);

        // Create tahe window.
        auto window = DialogsWindow::create(
            context,
            app,
            "dialogs",
            Size2I(1280, 960));

        // Show the window and run the application.
        window->show();
        app->run();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

