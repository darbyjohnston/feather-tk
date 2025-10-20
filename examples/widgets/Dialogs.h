// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/ProgressDialog.h>
#include <ftk/UI/ScrollWidget.h>

#include <ftk/Core/Timer.h>

using namespace ftk;

namespace widgets
{
    class Dialogs : public ftk::IWidget
    {
    protected:
        void _init(const std::shared_ptr<Context>&);

        Dialogs() = default;

    public:
        virtual ~Dialogs();

        static std::shared_ptr<Dialogs> create(const std::shared_ptr<Context>&);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        std::shared_ptr<ftk::ScrollWidget> _scrollWidget;
        std::shared_ptr<ftk::Timer> _progressTimer;
        std::shared_ptr<ftk::ProgressDialog> _progressDialog;
    };
}
