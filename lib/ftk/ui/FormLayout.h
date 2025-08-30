// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/ui/IWidget.h>

namespace ftk
{
    //! \name Layouts
    ///@{

    //! Form layout.
    class FormLayout : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        FormLayout();

    public:
        virtual ~FormLayout();

        //! Create a new layout.
        static std::shared_ptr<FormLayout> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Add a row.
        int addRow(const std::string&, const std::shared_ptr<IWidget>&);

        //! Remove a row.
        void removeRow(int);

        //! Remove a row.
        void removeRow(const std::shared_ptr<IWidget>&);

        //! Clear all of the rows.
        void clear();

        //! Set row visibility.
        void setRowVisible(int, bool);

        //! Set row visibility.
        void setRowVisible(const std::shared_ptr<IWidget>&, bool);

        //! Get the margin role.
        SizeRole getMarginRole() const;

        //! Set the margin role.
        void setMarginRole(SizeRole);

        //! Get the spacing role.
        SizeRole getSpacingRole() const;

        //! Set the spacing role.
        void setSpacingRole(SizeRole);

        //! Add a spacer.
        int addSpacer();

        //! Add a spacer.
        int addSpacer(SizeRole);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        FTK_PRIVATE();
    };

    ///@}
}
