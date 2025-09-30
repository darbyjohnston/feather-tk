// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/FormLayout.h>

using namespace ftk;

class Sliders : public IWidget
{
protected:
    void _init(
        const std::shared_ptr<Context>&,
        const std::shared_ptr<IWidget>&);

    Sliders() = default;

public:
    virtual ~Sliders();

    static std::shared_ptr<Sliders> create(
        const std::shared_ptr<Context>&,
        const std::shared_ptr<IWidget>&);

    void setGeometry(const Box2I&) override;
    void sizeHintEvent(const SizeHintEvent&) override;

private:
    std::shared_ptr<FormLayout> _layout;
};