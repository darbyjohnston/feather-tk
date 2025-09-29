// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/Ui/IWidget.h>

namespace ftk
{
    //! \name Text Widgets
    ///@{

    //! Search box widget.
    class SearchBox : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        SearchBox();

    public:
        virtual ~SearchBox();

        //! Create a new widget.
        static std::shared_ptr<SearchBox> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Get the text.
        const std::string& getText() const;

        //! Set the text.
        void setText(const std::string&);

        //! Set the callback.
        void setCallback(const std::function<void(const std::string&)>&);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        void _widgetUpdate();

        FTK_PRIVATE();
    };

    ///@}
}