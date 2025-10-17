// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "App.h"

#include "DocumentModel.h"
#include "MainWindow.h"
#include "SettingsModel.h"

#include <ftk/UI/DialogSystem.h>
#include <ftk/UI/FileBrowser.h>

using namespace ftk;

namespace examples
{
    namespace textedit
    {
        void App::_init(
            const std::shared_ptr<Context>& context,
            const std::vector<std::string>& argv)
        {
            _cmdLine.paths = CmdLineListArg<std::string>::create(
                "inputs",
                "Input paths.",
                true);

            ftk::App::_init(
                context,
                argv,
                "textedit",
                "Text edit example",
                { _cmdLine.paths });

            context->getSystem<FileBrowserSystem>()->setNativeFileDialog(false);

            _settingsModel = SettingsModel::create(context);

            _documentModel = DocumentModel::create(context);

            _recentFilesModel = RecentFilesModel::create(context);
            _recentFilesModel->setRecent(_settingsModel->getRecentFiles());

            _mainWindow = MainWindow::create(
                context,
                std::dynamic_pointer_cast<App>(shared_from_this()),
                "textedit",
                Size2I(1280, 960));
            _mainWindow->show();

            std::vector<std::filesystem::path> paths;
            for (const std::string& path : _cmdLine.paths->getList())
            {
                paths.push_back(std::filesystem::u8path(path));
            }
            if (!paths.empty())
            {
                open(paths);
            }
        }

        App::~App()
        {
            _settingsModel->setRecentFiles(_recentFilesModel->getRecent());
        }

        std::shared_ptr<App> App::create(
            const std::shared_ptr<Context>& context,
            const std::vector<std::string>& argv)
        {
            auto out = std::shared_ptr<App>(new App);
            out->_init(context, argv);
            return out;
        }

        const std::shared_ptr<SettingsModel>& App::getSettingsModel() const
        {
            return _settingsModel;
        }

        const std::shared_ptr<DocumentModel>& App::getDocumentModel() const
        {
            return _documentModel;
        }

        const std::shared_ptr<ftk::RecentFilesModel>& App::getRecentFilesModel() const
        {
            return _recentFilesModel;
        }

        const std::shared_ptr<MainWindow>& App::getMainWindow() const
        {
            return _mainWindow;
        }

        void App::open(const std::filesystem::path& path)
        {
            try
            {
                auto document = Document::create(_context, path);
                _documentModel->add(document);
                _recentFilesModel->addRecent(path);
            }
            catch (const std::exception& e)
            {
                _context->getSystem<DialogSystem>()->message("ERROR", e.what(), _mainWindow);
            }
        }

        void App::open(const std::vector<std::filesystem::path>& paths)
        {
            std::vector<std::string> errors;
            for (const auto& path : paths)
            {
                try
                {
                    auto document = Document::create(_context, path);
                    _documentModel->add(document);
                    _recentFilesModel->addRecent(path);
                }
                catch (const std::exception& e)
                {
                    errors.push_back(e.what());
                }
            }
            if (!errors.empty())
            {
                _context->getSystem<DialogSystem>()->message("ERROR", join(errors, '\n') , _mainWindow);
            }
        }

        void App::close(int index)
        {
            auto& docs = _documentModel->getList();
            if (index >= 0 && index < docs.size())
            {
                auto doc = docs[index];
                if (doc->isChanged())
                {
                    _context->getSystem<DialogSystem>()->confirm(
                        "Save File",
                        "File has unsaved changes, would you like to save them?",
                        _mainWindow,
                        [this, doc, index](bool value)
                        {
                            if (value)
                            {
                                try
                                {
                                    doc->save();
                                    _documentModel->close(index);
                                }
                                catch (const std::exception& e)
                                {
                                    _context->getSystem<DialogSystem>()->message("ERROR", e.what(), _mainWindow);
                                }
                            }
                        },
                        "Yes",
                        "No");
                }
                else
                {
                    _documentModel->close(index);
                }
            }
        }

        void App::closeAll()
        {
            bool changed = false;
            for (const auto& doc : _documentModel->getList())
            {
                changed |= doc->isChanged();
            }
            if (changed)
            {
                _context->getSystem<DialogSystem>()->confirm(
                    "Save Files",
                    "Files have unsaved changes, would you like to save them?",
                    _mainWindow,
                    [this](bool value)
                    {
                        if (value)
                        {
                            try
                            {
                                _documentModel->saveAll();
                                _documentModel->closeAll();
                            }
                            catch (const std::exception& e)
                            {
                                _context->getSystem<DialogSystem>()->message("ERROR", e.what(), _mainWindow);
                            }
                        }
                    },
                    "Yes",
                    "No");
            }
            else
            {
                _documentModel->closeAll();
            }
        }

        void App::save()
        {
            if (auto doc = _documentModel->getCurrent())
            {
                if (doc->getPath().empty())
                {
                    saveAs();
                }
                else
                {
                    try
                    {
                        doc->save();
                    }
                    catch (const std::exception& e)
                    {
                        _context->getSystem<DialogSystem>()->message("ERROR", e.what(), _mainWindow);
                    }
                }
            }
        }

        void App::saveAs()
        {
            if (auto doc = _documentModel->getCurrent())
            {
                auto fileBrowserSystem = _context->getSystem<FileBrowserSystem>();
                fileBrowserSystem->open(
                    _mainWindow,
                    [this, doc](const std::filesystem::path& path)
                    {
                        try
                        {
                            doc->saveAs(path);
                        }
                        catch (const std::exception& e)
                        {
                            _context->getSystem<DialogSystem>()->message("ERROR", e.what(), _mainWindow);
                        }
                    });
            }
        }
    }
}