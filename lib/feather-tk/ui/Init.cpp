// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/Init.h>

#include <feather-tk/ui/ClipboardSystem.h>
#include <feather-tk/ui/DialogSystem.h>
#include <feather-tk/ui/FileBrowser.h>
#include <feather-tk/ui/IconSystem.h>

#include <feather-tk/core/Context.h>

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
