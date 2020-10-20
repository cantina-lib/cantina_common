
#ifndef CANTINA_TIME_INTERNALCLOCK_INL
#define CANTINA_TIME_INTERNALCLOCK_INL

#pragma once

#include <cant/time/CustomExternalClock.hpp>
#include <cant/time/SystemExternalClock.hpp>

#include <cant/common/macro.hpp>

CANTINA_TIME_NAMESPACE_BEGIN

    CANT_INLINE
    InternalClock::
    InternalClock(UPtr<ExternalClock> externalClock)
    : m_externalClock(std::move(externalClock)),
      m_tStartAbsoluteExternal(),
      m_tStartRunningExternal(),
      m_tStopRunningExternal(),
      m_tLastInternal(),
      m_tNotRunningTotal(),
      m_isRunning(false)
    {
        reset();
    }

    CANT_INLINE
    bool
    InternalClock::
    isRunning() const
    {
        return m_isRunning;
    }

    CANT_INLINE
    void
    InternalClock::
    start()
    {
        if (!isRunning())
        {
            // updating the the total time not running.
            time_d const tNotRunning = m_tStopRunningExternal - m_tStartRunningExternal;
            m_tNotRunningTotal += tNotRunning;

            m_tStartRunningExternal = m_externalClock->getCurrentTimeSeconds();

            m_isRunning = true;
        }
    }

    CANT_INLINE
    void
    InternalClock::
    stop()
    {
        if (isRunning())
        {
            m_tStopRunningExternal = m_externalClock->getCurrentTimeSeconds();

            m_isRunning = false;
        }
    }

    CANT_INLINE
    void
    InternalClock::
    update()
    {
        if (isRunning())
        {
            m_tLastInternal = getCurrentTimeSeconds();
        }
        this->updateTime();
    }

    CANT_INLINE
    void
    InternalClock::
    updateTime()
    {
        m_externalClock->updateTime();
    }

    CANT_INLINE
    type_d
    InternalClock::
    getCurrentTimeSeconds() const
    {
        return m_externalClock->getCurrentTimeSeconds() - m_tNotRunningTotal;
    }

    CANT_INLINE
    type_d
    InternalClock::
    getDeltaTimeSeconds() const
    {
        CANT_MAYBEUNUSED time_d const aa = getCurrentTimeSeconds() - m_tLastInternal;
        return getCurrentTimeSeconds() - m_tLastInternal;
    }

    CANT_INLINE
    void
    InternalClock::
    reset()
    {
        m_tStartAbsoluteExternal = m_externalClock->getCurrentTimeSeconds();
        m_tNotRunningTotal = static_cast<time_d>(0);

        m_tStartRunningExternal = m_tStartAbsoluteExternal;
        m_tStopRunningExternal = m_tStartRunningExternal;

        m_tLastInternal = m_tStartAbsoluteExternal;
        // change to running state..? or not?
    }

    CANT_INLINE
    void
    InternalClock::
    setCustomTimeGetter(AbsoluteTimeGetter absoluteTimeGetter)
    {
        m_externalClock = CustomExternalClock::make(std::move(absoluteTimeGetter));
        reset();
    }


    CANT_INLINE
    UPtr<InternalClock>
    InternalClock::
    make(UPtr<ExternalClock> externalClock)
    {
        return UPtr<InternalClock>(new InternalClock(std::move(externalClock)));
    }


CANTINA_TIME_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TIME_INTERNALCLOCK_INL