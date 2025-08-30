// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/IButton.h>

namespace ftk
{
    //! \name Buttons
    ///@{
        
    //! Button group type.
    enum class ButtonGroupType
    {
        Click,
        Check,
        Radio,
        Toggle
    };

    //! Button group.
    class ButtonGroup : public std::enable_shared_from_this<ButtonGroup>
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            ButtonGroupType);

        ButtonGroup();

    public:
        ~ButtonGroup();

        //! Create a new button group.
        static std::shared_ptr<ButtonGroup> create(
            const std::shared_ptr<Context>&,
            ButtonGroupType);

        //! Get the buttons in the group.
        const std::vector<std::shared_ptr<IButton> >& getButtons() const;

        //! Add a button to the group.
        void addButton(const std::shared_ptr<IButton>&);

        //! Clear the buttons in the group.
        void clearButtons();

        //! Set whether the button is checked.
        void setChecked(int, bool = true);

        //! Set the clicked callback.
        void setClickedCallback(const std::function<void(int)>&);

        //! Set the checked callback.
        void setCheckedCallback(const std::function<void(int, bool)>&);

    private:
        FTK_PRIVATE();
    };
        
    ///@}
}
