// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <algorithm>

namespace ftk
{
    template<typename T>
    inline void ValueObserver<T>::_init(
        const std::shared_ptr<IObservableValue<T> >& value,
        const std::function<void(const T&)>& callback,
        ObserverAction action)
    {
        _value = value;
        _callback = callback;
        if (auto value = _value.lock())
        {
            value->_add(ValueObserver<T>::shared_from_this());
            if (ObserverAction::Trigger == action)
            {
                _callback(value->get());
            }
        }
    }

    template<typename T>
    inline ValueObserver<T>::~ValueObserver()
    {
        if (auto value = _value.lock())
        {
            value->_removeExpired();
        }
    }

    template<typename T>
    inline std::shared_ptr<ValueObserver<T> > ValueObserver<T>::create(
        const std::shared_ptr<IObservableValue<T> >& value,
        const std::function<void(const T&)>& callback,
        ObserverAction action)
    {
        std::shared_ptr<ValueObserver<T> > out(new ValueObserver<T>);
        out->_init(value, callback, action);
        return out;
    }

    template<typename T>
    inline void ValueObserver<T>::doCallback(const T& value)
    {
        _callback(value);
    }

    template<typename T>
    inline IObservableValue<T>::~IObservableValue()
    {}

    template<typename T>
    inline std::size_t IObservableValue<T>::getObserversCount() const
    {
        return _observers.size();
    }

    template<typename T>
    inline void IObservableValue<T>::_add(const std::weak_ptr<ValueObserver<T> >& observer)
    {
        _observers.push_back(observer);
    }

    template<typename T>
    inline void IObservableValue<T>::_removeExpired()
    {
        auto i = _observers.begin();
        while (i != _observers.end())
        {
            if (i->expired())
            {
                i = _observers.erase(i);
            }
            else
            {
                ++i;
            }
        }
    }

    template<typename T>
    inline ObservableValue<T>::ObservableValue(const T& value) :
        _value(value)
    {}

    template<typename T>
    inline std::shared_ptr<ObservableValue<T> > ObservableValue<T>::create()
    {
        return std::shared_ptr<ObservableValue<T> >(new ObservableValue<T>);
    }

    template<typename T>
    inline std::shared_ptr<ObservableValue<T> > ObservableValue<T>::create(const T& value)
    {
        return std::shared_ptr<ObservableValue<T> >(new ObservableValue<T>(value));
    }

    template<typename T>
    inline void ObservableValue<T>::setAlways(const T& value)
    {
        _value = value;
        for (const auto& i : IObservableValue<T>::_observers)
        {
            if (auto observer = i.lock())
            {
                observer->doCallback(_value);
            }
        }
    }

    template<typename T>
    inline bool ObservableValue<T>::setIfChanged(const T& value)
    {
        if (value == _value)
            return false;
        _value = value;
        for (const auto& i : IObservableValue<T>::_observers)
        {
            if (auto observer = i.lock())
            {
                observer->doCallback(_value);
            }
        }
        return true;
    }

    template<typename T>
    inline const T& ObservableValue<T>::get() const
    {
        return _value;
    }
}
