// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/IWidget.h>

#include <ftk/Core/Image.h>

namespace ftk
{
    //! \name Images
    ///@{
        
    //! SVG widget.
    class SvgWidget : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        SvgWidget();

    public:
        virtual ~SvgWidget();

        //! Create a new widget.
        static std::shared_ptr<SvgWidget> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Get the SVG data.
        const std::vector<uint8_t>& getSVGData() const;

        //! Set the SVG data.
        void setSVGData(const std::vector<uint8_t>&);

        //! Get the SVG width.
        int getSVGWidth() const;

        //! Set the SVG width.
        void setSVGWidth(int);

        //! Get the margin role.
        SizeRole getMarginRole() const;

        //! Set the margin role.
        void setMarginRole(SizeRole);

        void sizeHintEvent(const SizeHintEvent&) override;
        void drawEvent(const Box2I&, const DrawEvent&) override;

    private:
        FTK_PRIVATE();
    };
        
    ///@}
}
