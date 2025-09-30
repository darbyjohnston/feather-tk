// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/IWidget.h>

namespace ftk
{
    //! \name Layouts
    ///@{
        
    //! Divider widget.
    class Divider : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            Orientation,
            const std::shared_ptr<IWidget>& parent);

        Divider();

    public:
        virtual ~Divider();

        //! Create a new widget.
        static std::shared_ptr<Divider> create(
            const std::shared_ptr<Context>&,
            Orientation,
            const std::shared_ptr<IWidget>& parent = nullptr);

        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        FTK_PRIVATE();
    };
        
    ///@}
}
