// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/UI/ClipboardSystem.h>

#include <SDL2/SDL.h>

namespace ftk
{
    struct ClipboardSystem::Private
    {};

    ClipboardSystem::ClipboardSystem(const std::shared_ptr<Context>& context) :
        ISystem(context, "ftk::ClipboardSystem"),
        _p(new Private)
    {}

    ClipboardSystem::~ClipboardSystem()
    {}

    std::shared_ptr<ClipboardSystem> ClipboardSystem::create(const std::shared_ptr<Context>& context)
    {
        return std::shared_ptr<ClipboardSystem>(new ClipboardSystem(context));
    }

    std::string ClipboardSystem::getText() const
    {
        std::string out;
        if (char* buf = SDL_GetClipboardText())
        {
            out = std::string(buf);
            SDL_free(&buf);
        }
        return out;
    }

    void ClipboardSystem::setText(const std::string& value)
    {
        SDL_SetClipboardText(value.c_str());
    }
}