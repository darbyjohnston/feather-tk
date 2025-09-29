// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/Label.h>

#include <feather-tk/core/LogSystem.h>
#include <feather-tk/core/Timer.h>

namespace examples
{
    namespace textedit
    {
        class StatusBar : public ftk::IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<ftk::IWidget>& parent);

            StatusBar() = default;

        public:
            virtual ~StatusBar();

            static std::shared_ptr<StatusBar> create(
                const std::shared_ptr<ftk::Context>&,
                const std::shared_ptr<ftk::IWidget>& parent = nullptr);

            ftk::FontRole getFontRole() const;

            void setGeometry(const ftk::Box2I&) override;
            void sizeHintEvent(const ftk::SizeHintEvent&) override;

        private:
            std::shared_ptr<ftk::Label> _label;

            std::shared_ptr<ftk::Timer> _timer;

            std::shared_ptr<ftk::ListObserver<ftk::LogItem> > _logObserver;
        };
    }
}