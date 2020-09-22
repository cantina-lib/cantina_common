//
// Created by binabik on 01/09/2020.
//

#ifndef CANTINA_TIME_SYSTEMCLOCK_INL
#define CANTINA_TIME_SYSTEMCLOCK_INL

#pragma once

#include <cant/common/macro.hpp>

CANTINA_TIME_NAMESPACE_BEGIN

    CANT_INLINE
    SystemExternalClock::
    SystemExternalClock()
        : m_tStart(StdClock::now()),
          m_tAbsolute(),
          m_tLast()
    {}

    CANT_INLINE
    void
    SystemExternalClock::
    updateTime()
    {
        m_tLast = m_tAbsolute;
        m_tAbsolute = StdClock::now();
    }

    CANT_INLINE
    type_d
    SystemExternalClock::
    getCurrentTimeSeconds() const
    {
        return static_cast<type_d>((m_tAbsolute - m_tStart).count());
    }

    CANT_INLINE
    type_d
    SystemExternalClock::
    getDeltaTimeSeconds() const
    {
        return static_cast<type_d>((m_tAbsolute - m_tLast).count());
    }

    CANT_INLINE
    UPtr <ExternalClock>
    SystemExternalClock::
    make()
    {
        return std::unique_ptr<SystemExternalClock>(new SystemExternalClock());
    }

CANTINA_TIME_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TIME_SYSTEMCLOCK_INL
