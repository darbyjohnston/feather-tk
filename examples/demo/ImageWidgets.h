// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/RowLayout.h>

using namespace ftk;

class ImageWidgets : public IWidget
{
protected:
    void _init(
        const std::shared_ptr<Context>&,
        const std::shared_ptr<IWidget>&);

    ImageWidgets() = default;

public:
    virtual ~ImageWidgets();

    static std::shared_ptr<ImageWidgets> create(
        const std::shared_ptr<Context>&,
        const std::shared_ptr<IWidget>&);

    void setGeometry(const Box2I&) override;
    void sizeHintEvent(const SizeHintEvent&) override;

private:
    std::shared_ptr<HorizontalLayout> _layout;
};