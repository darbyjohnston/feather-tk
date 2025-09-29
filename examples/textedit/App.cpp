// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "App.h"

#include "DocumentModel.h"
#include "MainWindow.h"

#include <feather-tk/ui/DialogSystem.h>
#include <feather-tk/ui/FileBrowser.h>

#include <feather-tk/core/FileIO.h>

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

            _documentModel = DocumentModel::create(context);

            _mainWindow = MainWindow::create(
                context,
                std::dynamic_pointer_cast<App>(shared_from_this()),
                "textedit",
                Size2I(1280, 960));
            _mainWindow->show();

            for (const auto& input : _cmdLine.paths->getList())
            {
                open(input);
            }
        }

        std::shared_ptr<App> App::create(
            const std::shared_ptr<Context>& context,
            const std::vector<std::string>& argv)
        {
            auto out = std::shared_ptr<App>(new App);
            out->_init(context, argv);
            return out;
        }

        const std::shared_ptr<DocumentModel>& App::getDocumentModel() const
        {
            return _documentModel;
        }

        void App::open(const std::filesystem::path& path)
        {
            try
            {
                auto document = Document::create(_context, path);
                document->setLines(readLines(path));
                _documentModel->add(document);
            }
            catch (const std::exception& e)
            {
                _context->getSystem<LogSystem>()->print("App", e.what(), LogType::Error);
            }
        }
    }
}