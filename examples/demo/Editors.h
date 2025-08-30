// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/FormLayout.h>

using namespace ftk;

class Editors : public IWidget
{
protected:
    void _init(
        const std::shared_ptr<Context>&,
        const std::shared_ptr<IWidget>&);

    Editors() = default;

public:
    virtual ~Editors();

    static std::shared_ptr<Editors> create(
        const std::shared_ptr<Context>&,
        const std::shared_ptr<IWidget>&);

    void setGeometry(const Box2I&) override;
    void sizeHintEvent(const SizeHintEvent&) override;

private:
    std::shared_ptr<FormLayout> _layout;
};