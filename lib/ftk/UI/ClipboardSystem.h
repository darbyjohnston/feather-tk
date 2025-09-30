// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/Core/ISystem.h>
#include <ftk/Core/ObservableValue.h>

namespace ftk
{
    //! Clipboard system.
    class ClipboardSystem : public ISystem
    {
    protected:
        ClipboardSystem(const std::shared_ptr<Context>&);

    public:
        virtual ~ClipboardSystem();

        //! Create a new system.
        static std::shared_ptr<ClipboardSystem> create(
            const std::shared_ptr<Context>&);

        //! Get the clipboard text.
        const std::string& getText() const;

        //! Observe the clipboard text.
        std::shared_ptr<IObservableValue<std::string> > observeText() const;

        //! Set the clipboard text.
        void setText(const std::string&);

    private:
        FTK_PRIVATE();
    };

    ///@}
}