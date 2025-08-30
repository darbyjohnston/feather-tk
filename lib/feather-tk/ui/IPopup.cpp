// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/IPopup.h>

namespace ftk
{
    void IPopup::_init(
        const std::shared_ptr<Context>& context,
        const std::string& objectName,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, objectName, parent);
    }

    IPopup::IPopup()
    {}

    IPopup::~IPopup()
    {}
}
