// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/ui/Init.h>

#include <ftk/ui/ClipboardSystem.h>
#include <ftk/ui/DialogSystem.h>
#include <ftk/ui/FileBrowser.h>
#include <ftk/ui/IconSystem.h>

#include <ftk/core/Context.h>

namespace ftk
{
    void uiInit(const std::shared_ptr<Context>& context)
    {
        if (!context->getSystem<ClipboardSystem>())
        {
            context->addSystem(ClipboardSystem::create(context));
        }
        if (!context->getSystem<DialogSystem>())
        {
            context->addSystem(DialogSystem::create(context));
        }
        if (!context->getSystem<FileBrowserSystem>())
        {
            context->addSystem(FileBrowserSystem::create(context));
        }
        if (!context->getSystem<IconSystem>())
        {
            context->addSystem(IconSystem::create(context));
        }
    }
}
