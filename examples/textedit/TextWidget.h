// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/ui/IWidget.h>

namespace ftk
{
    namespace examples
    {
        namespace textedit
        {
            class TextWidget : public IWidget
            {
            protected:
                void _init(
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<IWidget>& parent);

                TextWidget();

            public:
                virtual ~TextWidget();

                static std::shared_ptr<TextWidget> create(
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<IWidget>& parent = nullptr);

            private:
                FTK_PRIVATE();
            };
        }
    }
}
