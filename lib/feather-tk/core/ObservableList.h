// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/Observable.h>
#include <feather-tk/core/Util.h>

#include <functional>
#include <memory>
#include <vector>

namespace feather_tk
{
    //! \name Observables
    ///@{
        
    template<typename T>
    class IObservableList;

    //! Invalid index.
    static const std::size_t ObservableListInvalidIndex = static_cast<std::size_t>(-1);

    //! List observer.
    template<typename T>
    class ListObserver : public std::enable_shared_from_this<ListObserver<T> >
    {
        FEATHER_TK_NON_COPYABLE(ListObserver);

    protected:
        void _init(
            const std::shared_ptr<IObservableList<T> >&,
            const std::function<void(const std::vector<T>&)>&,
            ObserverAction);

        ListObserver() = default;

    public:
        ~ListObserver();

        //! Create a new list observer.
        static std::shared_ptr<ListObserver<T> > create(
            const std::shared_ptr<IObservableList<T> >&,
            const std::function<void(const std::vector<T>&)>&,
            ObserverAction = ObserverAction::Trigger);

        //! Execute the callback.
        void doCallback(const std::vector<T>&);

    private:
        std::function<void(const std::vector<T>&)> _callback;
        std::weak_ptr<IObservableList<T> > _value;
    };

    //! Base class for observable lists.
    template<typename T>
    class IObservableList
    {
    public:
        virtual ~IObservableList() = 0;

        //! Get the list.
        virtual const std::vector<T>& get() const = 0;

        //! Get the list size.
        virtual std::size_t getSize() const = 0;

        //! Get whether the list is empty.
        virtual bool isEmpty() const = 0;

        //! Get a list item.
        virtual T getItem(std::size_t) const = 0;

        //! Does the list contain the given item?
        virtual bool contains(const T&) const = 0;

        //! Get the index of the given item.
        virtual std::size_t indexOf(const T&) const = 0;

        //! Get the number of observers.
        std::size_t getObserversCount() const;

    protected:
        void _add(const std::weak_ptr<ListObserver<T> >&);
        void _removeExpired();

        std::vector<std::weak_ptr<ListObserver<T> > > _observers;

        friend ListObserver<T>;
    };

    //! Observable list.
    template<typename T>
    class ObservableList : public IObservableList<T>
    {
        FEATHER_TK_NON_COPYABLE(ObservableList);

    protected:
        ObservableList() = default;
        explicit ObservableList(const std::vector<T>&);

    public:
        //! Create a new list.
        static std::shared_ptr<ObservableList<T> > create();

        //! Create a new list with the given value.
        static std::shared_ptr<ObservableList<T> > create(const std::vector<T>&);

        //! Set the list.
        void setAlways(const std::vector<T>&);

        //! Set the list only if it has changed.
        bool setIfChanged(const std::vector<T>&);

        //! Clear the list.
        void clear();

        //! Set a list item.
        void setItem(std::size_t, const T&);

        //! Set a list item only if it has changed.
        void setItemOnlyIfChanged(std::size_t, const T&);

        //! Append a list item.
        void pushBack(const T&);

        //! Remove an item.
        void removeItem(std::size_t);

        const std::vector<T>& get() const override;
        std::size_t getSize() const override;
        bool isEmpty() const override;
        T getItem(std::size_t) const override;
        bool contains(const T&) const override;
        std::size_t indexOf(const T&) const override;

    private:
        std::vector<T> _value;
    };
        
    ///@}
}

#include <feather-tk/core/ObservableListInline.h>

