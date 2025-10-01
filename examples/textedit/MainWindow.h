// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/MainWindow.h>
#include <ftk/UI/RowLayout.h>
#include <ftk/UI/TabWidget.h>
#include <ftk/UI/TextEdit.h>

namespace examples
{
    namespace textedit
    {
        class App;
        class Document;
        class MenuBar;
        class StatusBar;

        class MainWindow : public ftk::MainWindow
        {
        protected:
            void _init(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<App>&,
                const std::string& name,
                const ftk::Size2I&);

            MainWindow() = default;

        public:
            virtual ~MainWindow();

            static std::shared_ptr<MainWindow> create(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<App>&,
                const std::string& name,
                const ftk::Size2I&);

        protected:
            void _drop(const std::vector<std::string>&);
 
        private:

            std::weak_ptr<App> _app;

            std::shared_ptr<MenuBar> _menuBar;
            std::shared_ptr<ftk::TabWidget> _tabWidget;
            std::vector<std::shared_ptr<ftk::TextEdit> > _textEdits;
            std::shared_ptr<StatusBar> _statusBar;
            std::shared_ptr<ftk::VerticalLayout> _layout;

            std::shared_ptr<ftk::ValueObserver<std::shared_ptr<Document> > > _addDocumentObserver;
            std::shared_ptr<ftk::ValueObserver<int> > _removeDocumentObserver;
            std::shared_ptr<ftk::ValueObserver<bool> > _clearDocumentsObserver;
            std::shared_ptr<ftk::ValueObserver<int> > _currentDocumentObserver;
            std::shared_ptr<ftk::ValueObserver<ftk::FontRole> > _fontObserver;
        };
    }
}