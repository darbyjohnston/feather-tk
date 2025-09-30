// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/Bellows.h>

#include <ftk/UI/IButton.h>

namespace ftk
{
    class BellowsButton : public IButton
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        BellowsButton();

    public:
        virtual ~BellowsButton();

        static std::shared_ptr<BellowsButton> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;
        void clipEvent(const Box2I&, bool) override;
        void drawEvent(const Box2I&, const DrawEvent&) override;
        void keyPressEvent(KeyEvent&) override;
        void keyReleaseEvent(KeyEvent&) override;

    private:
        FTK_PRIVATE();
    };
}
