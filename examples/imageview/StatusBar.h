// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/Label.h>
#include <ftk/UI/RowLayout.h>

namespace examples
{
    namespace imageview
    {
        class App;
        class Document;

        //! Status bar widget.
        class StatusBar : public ftk::IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<App>&,
                const std::shared_ptr<ftk::IWidget>& parent);

            StatusBar() = default;

        public:
            virtual ~StatusBar();

            //! Create a new widget.
            static std::shared_ptr<StatusBar> create(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<App>&,
                const std::shared_ptr<ftk::IWidget>& parent = nullptr);

            void setGeometry(const ftk::Box2I&) override;
            void sizeHintEvent(const ftk::SizeHintEvent&) override;

        private:
            std::map<std::string, std::shared_ptr<ftk::Label> > _labels;
            std::shared_ptr<ftk::HorizontalLayout> _layout;

            std::shared_ptr<ftk::ValueObserver<std::shared_ptr<Document> > > _currentObserver;
        };
    }
}