// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/UI/DoubleModel.h>

#include <ftk/Core/Math.h>

namespace ftk
{
    struct DoubleModel::Private
    {
        std::shared_ptr<ObservableValue<double> > value;
        std::shared_ptr<ObservableValue<RangeD> > range;
        double step = 0.1;
        double largeStep = 1.0;
        std::shared_ptr<ObservableValue<bool> > hasDefaultValue;
        std::shared_ptr<ObservableValue<double> > defaultValue;
    };

    void DoubleModel::_init(const std::shared_ptr<Context>&)
    {
        FTK_P();
        p.value = ObservableValue<double>::create(0.0);
        p.range = ObservableValue<RangeD>::create(RangeD(0.0, 1.0));
        p.hasDefaultValue = ObservableValue<bool>::create(false);
        p.defaultValue = ObservableValue<double>::create(0.0);
    }

    DoubleModel::DoubleModel() :
        _p(new Private)
    {}

    DoubleModel::~DoubleModel()
    {}

    std::shared_ptr<DoubleModel> DoubleModel::create(
        const std::shared_ptr<Context>& context)
    {
        auto out = std::shared_ptr<DoubleModel>(new DoubleModel);
        out->_init(context);
        return out;
    }

    double DoubleModel::getValue() const
    {
        return _p->value->get();
    }

    std::shared_ptr<IObservableValue<double> > DoubleModel::observeValue() const
    {
        return _p->value;
    }

    void DoubleModel::setValue(double value)
    {
        FTK_P();
        const RangeD& range = p.range->get();
        const double tmp = clamp(value, range.min(), range.max());
        _p->value->setIfChanged(tmp);
    }

    const RangeD& DoubleModel::getRange() const
    {
        return _p->range->get();
    }

    std::shared_ptr<IObservableValue<RangeD> > DoubleModel::observeRange() const
    {
        return _p->range;
    }

    void DoubleModel::setRange(const RangeD& range)
    {
        FTK_P();
        if (p.range->setIfChanged(range))
        {
            setValue(p.value->get());
        }
    }

    double DoubleModel::getStep() const
    {
        return _p->step;
    }

    void DoubleModel::setStep(double value)
    {
        _p->step = value;
    }

    void DoubleModel::incrementStep()
    {
        FTK_P();
        setValue(p.value->get() + p.step);
    }

    void DoubleModel::decrementStep()
    {
        FTK_P();
        setValue(p.value->get() - p.step);
    }

    double DoubleModel::getLargeStep() const
    {
        return _p->largeStep;
    }

    void DoubleModel::setLargeStep(double value)
    {
        _p->largeStep = value;
    }

    void DoubleModel::incrementLargeStep()
    {
        FTK_P();
        setValue(p.value->get() + p.largeStep);
    }

    void DoubleModel::decrementLargeStep()
    {
        FTK_P();
        setValue(p.value->get() - p.largeStep);
    }

    bool DoubleModel::hasDefaultValue() const
    {
        return _p->hasDefaultValue->get();
    }

    std::shared_ptr<IObservableValue<bool> > DoubleModel::observeHasDefaultValue() const
    {
        return _p->hasDefaultValue;
    }

    double DoubleModel::getDefaultValue() const
    {
        return _p->defaultValue->get();
    }

    std::shared_ptr<IObservableValue<double> > DoubleModel::observeDefaultValue() const
    {
        return _p->defaultValue;
    }

    void DoubleModel::setDefaultValue(double value)
    {
        _p->defaultValue->setIfChanged(value);
        _p->hasDefaultValue->setIfChanged(true);
    }

    void DoubleModel::setDefaultValue()
    {
        setValue(_p->defaultValue->get());
    }

    void DoubleModel::clearDefaultValue()
    {
        _p->hasDefaultValue->setIfChanged(false);
    }
}