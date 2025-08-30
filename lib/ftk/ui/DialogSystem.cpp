// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/ui/DialogSystem.h>

#include <ftk/ui/ConfirmDialog.h>
#include <ftk/ui/MessageDialog.h>

namespace ftk
{
    struct DialogSystem::Private
    {
        std::shared_ptr<MessageDialog> messageDialog;
        std::shared_ptr<ConfirmDialog> confirmDialog;
    };

    DialogSystem::DialogSystem(const std::shared_ptr<Context>& context) :
        ISystem(context, "ftk::DialogSystem"),
        _p(new Private)
    {}

    DialogSystem::~DialogSystem()
    {}

    std::shared_ptr<DialogSystem> DialogSystem::create(const std::shared_ptr<Context>& context)
    {
        return std::shared_ptr<DialogSystem>(new DialogSystem(context));
    }

    void DialogSystem::message(
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWindow>& window)
    {
        FTK_P();
        if (auto context = _context.lock())
        {
            p.messageDialog = MessageDialog::create(context, title, text);
            p.messageDialog->open(window);
            p.messageDialog->setCallback(
                [this]
                {
                    _p->messageDialog->close();
                });
            p.messageDialog->setCloseCallback(
                [this]
                {
                    _p->messageDialog.reset();
                });
        }
    }

    void DialogSystem::confirm(
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWindow>& window,
        const std::function<void(bool)>& callback)
    {
        FTK_P();
        if (auto context = _context.lock())
        {
            p.confirmDialog = ConfirmDialog::create(context, title, text);
            p.confirmDialog->open(window);
            p.confirmDialog->setCallback(
                [this, callback](bool value)
                {
                    callback(value);
                    _p->confirmDialog->close();
                });
            p.confirmDialog->setCloseCallback(
                [this]
                {
                    _p->confirmDialog.reset();
                });
        }
    }
}