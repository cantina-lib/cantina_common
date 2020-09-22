//
// Created by binabik on 17/09/2020.
//

#ifndef CANTINA_TIME_CLOCK_INL
#define CANTINA_TIME_CLOCK_INL

#pragma once

#include <cant/common/macro.hpp>

CANTINA_TIME_NAMESPACE_BEGIN

    CANT_INLINE
    Clock::
    Clock() = default;

    CANT_INLINE
    Clock::
    ~Clock() = default;

    CANT_INLINE
    time_d
    Clock::
    getCurrentTime() const
    {
        return c_inMilliseconds * getCurrentTimeSeconds();
    }

    CANT_INLINE
    time_d
    Clock::
    getDeltaTime() const
    {
        return c_inMilliseconds * getDeltaTimeSeconds();
    }





CANTINA_TIME_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TIME_CLOCK_INL
