// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/UI/ClipboardSystem.h>

#include <SDL2/SDL.h>

namespace ftk
{
    struct ClipboardSystem::Private
    {
        std::shared_ptr<ObservableValue<std::string> > text;
    };

    ClipboardSystem::ClipboardSystem(const std::shared_ptr<Context>& context) :
        ISystem(context, "ftk::ClipboardSystem"),
        _p(new Private)
    {
        FTK_P();
        p.text = ObservableValue<std::string>::create();
    }

    ClipboardSystem::~ClipboardSystem()
    {}

    std::shared_ptr<ClipboardSystem> ClipboardSystem::create(const std::shared_ptr<Context>& context)
    {
        return std::shared_ptr<ClipboardSystem>(new ClipboardSystem(context));
    }

    const std::string& ClipboardSystem::getText() const
    {
        return _p->text->get();
    }

    std::shared_ptr<IObservableValue<std::string> > ClipboardSystem::observeText() const
    {
        return _p->text;
    }

    void ClipboardSystem::setText(const std::string& value)
    {
        if (_p->text->setIfChanged(value))
        {
            SDL_SetClipboardText(value.c_str());
        }
    }
}