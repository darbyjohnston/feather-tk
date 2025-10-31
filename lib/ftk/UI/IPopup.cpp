// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#include <ftk/UI/IPopup.h>

namespace ftk
{
    void IPopup::_init(
        const std::shared_ptr<Context>& context,
        const std::string& objectName,
        const std::shared_ptr<IWidget>& parent)
    {
        IMouseWidget::_init(context, objectName, parent);
    }

    IPopup::IPopup()
    {}

    IPopup::~IPopup()
    {}
}
