// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/Ui/App.h>
#include <ftk/Ui/Style.h>

#include <ftk/Core/CmdLine.h>
#include <ftk/Core/ObservableValue.h>

#include <filesystem>

namespace examples
{
    namespace textedit
    {
        class DocumentModel;
        class MainWindow;

        class App : public ftk::App
        {
        protected:
            void _init(
                const std::shared_ptr<ftk::Context>&,
                const std::vector<std::string>& argv);

            App() = default;

        public:
            virtual ~App() = default;

            static std::shared_ptr<App> create(
                const std::shared_ptr<ftk::Context>&,
                const std::vector<std::string>&);

            const std::shared_ptr<DocumentModel>& getDocumentModel() const;

            void open(const std::filesystem::path&);
            void open(const std::vector<std::filesystem::path>&);

        private:
            struct CmdLine
            {
                std::shared_ptr<ftk::CmdLineListArg<std::string> > paths;
            };
            CmdLine _cmdLine;
            std::shared_ptr<DocumentModel> _documentModel;
            std::shared_ptr<MainWindow> _mainWindow;
        };
    }
}