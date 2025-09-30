// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/Event.h>

namespace ftk
{
    //! \name Actions
    ///@{

    //! Action.
    class Action : public std::enable_shared_from_this<Action>
    {
    protected:
        void _init(
            const std::string&               text,
            const std::string&               icon,
            Key                              shortcut,
            int                              shortcutModifiers,
            const std::function<void(void)>& callback,
            const std::function<void(bool)>& checkedCallback);

        Action();

    public:
        ~Action();

        //! \name Create
        ///@{

        static std::shared_ptr<Action> create(
            const std::string&               text,
            const std::function<void(void)>& callback);

        static std::shared_ptr<Action> create(
            const std::string&               text,
            const std::string&               icon,
            const std::function<void(void)>& callback);

        static std::shared_ptr<Action> create(
            const std::string&               text,
            Key                              shortcut,
            int                              shortcutModifiers,
            const std::function<void(void)>& callback);

        static std::shared_ptr<Action> create(
            const std::string&               text,
            const std::string&               icon,
            Key                              shortcut,
            int                              shortcutModifiers,
            const std::function<void(void)>& callback);

        static std::shared_ptr<Action> create(
            const std::string&               text,
            const std::function<void(bool)>& checkedCallback);

        static std::shared_ptr<Action> create(
            const std::string&               text,
            const std::string&               icon,
            const std::function<void(bool)>& checkedCallback);

        static std::shared_ptr<Action> create(
            const std::string&               text,
            Key                              shortcut,
            int                              shortcutModifiers,
            const std::function<void(bool)>& checkedCallback);

        static std::shared_ptr<Action> create(
            const std::string&               text,
            const std::string&               icon,
            Key                              shortcut,
            int                              shortcutModifiers,
            const std::function<void(bool)>& checkedCallback);

        ///@}

        //! \name Text
        ///@{

        const std::string& getText() const;
        std::shared_ptr<IObservableValue<std::string> > observeText() const;
        void setText(const std::string&);

        ///@}

        //! \name Icon
        ///@{

        const std::string& getIcon() const;
        const std::string& getCheckedIcon() const;
        std::shared_ptr<IObservableValue<std::string> > observeIcon() const;
        std::shared_ptr<IObservableValue<std::string> > observeCheckedIcon() const;
        void setIcon(const std::string&);
        void setCheckedIcon(const std::string&);

        ///@}

        //! \name Shortcut
        ///@{

        Key getShortcut() const;
        int getShortcutModifiers() const;
        std::shared_ptr<IObservableValue<Key> > observeShortcut() const;
        std::shared_ptr<IObservableValue<int> > observeShortcutModifiers() const;
        void setShortcut(Key);
        void setShortcutModifiers(int);

        ///@}

        //! \name Callback
        ///@{

        void doCallback();

        ///@}

        //! \name Checkable
        ///@{

        bool isCheckable() const;
        bool isChecked() const;
        std::shared_ptr<IObservableValue<bool> > observeCheckable() const;
        std::shared_ptr<IObservableValue<bool> > observeChecked() const;
        void setCheckable(bool);
        void setChecked(bool);
        void doCheckedCallback(bool);

        ///@}

        //! \name Enabled
        ///@{

        bool isEnabled() const;
        std::shared_ptr<IObservableValue<bool> > observeEnabled() const;
        void setEnabled(bool);

        ///@}

        //! \name Tooltip
        ///@{

        const std::string& getTooltip() const;
        std::shared_ptr<IObservableValue<std::string> > observeTooltip() const;
        void setTooltip(const std::string&);

        ///@}

    private:
        FTK_PRIVATE();
    };

    ///@}
}
