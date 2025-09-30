// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/GridLayout.h>

using namespace ftk;

class Icons : public IWidget
{
protected:
    void _init(
        const std::shared_ptr<Context>&,
        const std::shared_ptr<IWidget>&);

    Icons() = default;

public:
    virtual ~Icons();

    static std::shared_ptr<Icons> create(
        const std::shared_ptr<Context>&,
        const std::shared_ptr<IWidget>&);

    void setGeometry(const Box2I&) override;
    void sizeHintEvent(const SizeHintEvent&) override;

private:
    std::shared_ptr<GridLayout> _layout;
};