// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/ObservableValue.h>
#include <feather-tk/core/Range.h>

namespace feather_tk
{
    class Context;
    
    //! \name Numeric Widgets
    ///@{
        
    //! Integer value model.
    class IntModel : public std::enable_shared_from_this<IntModel>
    {
        FEATHER_TK_NON_COPYABLE(IntModel);

        void _init(const std::shared_ptr<Context>&);

    protected:
        IntModel();

    public:
        ~IntModel();

        //! Create a new model.
        static std::shared_ptr<IntModel> create(
            const std::shared_ptr<Context>&);

        //! \name Value
        ///@{

        //! Get the value.
        int getValue() const;

        //! Observe the value.
        std::shared_ptr<IObservableValue<int> > observeValue() const;

        //! Set the value.
        void setValue(int);

        ///@}

        //! \name Range
        ///@{

        //! Get the range.
        const RangeI& getRange() const;

        //! Observe the range.
        std::shared_ptr<IObservableValue<RangeI> > observeRange() const;

        //! Set the range.
        void setRange(const RangeI&);

        ///@}

        //! \name Increment
        ///@{

        //! Get the increment step.
        int getStep() const;

        //! Set the increment step.
        void setStep(int);

        //! Increment the value by a step.
        void incrementStep();

        //! Decrement the value by a step.
        void decrementStep();

        //! Get the increment large step.
        int getLargeStep() const;

        //! Set the increment large step.
        void setLargeStep(int);

        //! Increment the value by a large step.
        void incrementLargeStep();

        //! Decrement the value by a large step.
        void decrementLargeStep();

        ///@}

        //! \name Default Value
        ///@{

        //! Get whether there is a default value.
        bool hasDefaultValue() const;

        //! Observe whether there is a default value.
        std::shared_ptr<IObservableValue<bool> > observeHasDefaultValue() const;

        //! Observe the default value.
        std::shared_ptr<IObservableValue<int> > observeDefaultValue() const;

        //! Get the default value.
        int getDefaultValue() const;

        //! Set the default value.
        void setDefaultValue(int);

        //! Set the value to the default value.
        void setDefaultValue();

        //! Clear the default value.
        void clearDefaultValue();

        ///@}

    private:
        FEATHER_TK_PRIVATE();
    };

    ///@}
}
