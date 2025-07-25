// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/ISystem.h>

#include <functional>

namespace feather_tk
{
    //! \name Timers
    ///@{
        
    //! Timer.
    class Timer : public std::enable_shared_from_this<Timer>
    {
        FEATHER_TK_NON_COPYABLE(Timer);

    protected:
        void _init(const std::shared_ptr<Context>&);

        Timer();

    public:
        ~Timer();

        //! Create a new timer.
        static std::shared_ptr<Timer> create(
            const std::shared_ptr<Context>&);

        //! Does the timer repeat?
        bool isRepeating() const;

        //! Set whether the timer repeats.
        void setRepeating(bool);

        //! Start the timer.
        void start(
            const std::chrono::microseconds& timeout,
            const std::function<void(void)>& callback);

        //! Start the timer.
        void start(
            const std::chrono::microseconds& timeout,
            const std::function<void(
                const std::chrono::steady_clock::time_point&,
                const std::chrono::microseconds&)>& callback);

        //! Stop the timer.
        void stop();

        //! Is the timer active?
        bool isActive() const;

        //! Get the timeout.
        const std::chrono::microseconds& getTimeout() const;

        void tick();

    private:
        FEATHER_TK_PRIVATE();
    };

    //! Timer system.
    class TimerSystem : public ISystem
    {
    protected:
        TimerSystem(const std::shared_ptr<Context>&);

    public:
        virtual ~TimerSystem();

        static std::shared_ptr<TimerSystem> create(
            const std::shared_ptr<Context>&);

        void addTimer(const std::shared_ptr<Timer>&);

        void tick() override;
        std::chrono::milliseconds getTickTime() const override;

    private:
        FEATHER_TK_PRIVATE();
    };
        
    ///@}
}
