// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/ui/IWidget.h>

namespace ftk
{
    //! \name Chart Widgets
    ///@{

    //! Pie chart data.
    struct PieChartData
    {
        PieChartData() = default;
        PieChartData(
            float                percentage,
            const Color4F& color);

        float         percentage = 0.F;
        Color4F color;

        bool operator == (const PieChartData&) const;
        bool operator != (const PieChartData&) const;
    };

    //! Pie chart widget.
    class PieChart : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        PieChart();

    public:
        virtual ~PieChart();

        //! Create a new widget.
        static std::shared_ptr<PieChart> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Get the pie chart data.
        const std::vector<PieChartData>& getData() const;

        //! Set the pie chart data.
        void setData(const std::vector<PieChartData>&);

        //! Set the size multiplier.
        int getSizeMult() const;

        //! Set the size multiplier.
        void setSizeMult(int);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;
        void clipEvent(const Box2I&, bool) override;
        void drawEvent(const Box2I&, const DrawEvent&) override;

    private:
        FTK_PRIVATE();
    };

    ///@}
}
