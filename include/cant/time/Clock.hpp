//
// Created by piptouque on 29/04/2020.
//

#ifndef CANTINA_TIME_CLOCK_HPP
#define CANTINA_TIME_CLOCK_HPP

#pragma once

#include <cant/time/common/types.hpp>

#include <cant/common/macro.hpp>
CANTINA_TIME_NAMESPACE_BEGIN

class Clock
{
   public:
    /** -- methods -- **/
    Clock();
    virtual ~Clock();

    virtual void
      updateTime()
      = 0;

    CANT_NODISCARD time_d
      getCurrentTime() const;
    CANT_NODISCARD time_d
      getDeltaTime() const;

   protected:
    /** -- methods -- **/
    CANT_NODISCARD virtual type_d
      getCurrentTimeSeconds() const = 0;
    CANT_NODISCARD virtual type_d
      getDeltaTimeSeconds() const = 0;

   private:
    /** -- fields -- **/
    // constants
    static CANT_CONSTEXPR type_d c_inMilliseconds = 1000;
};

class ExternalClock : public Clock
{
    friend class InternalClock;
};

CANTINA_TIME_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/time/Clock.inl>

#endif  // CANTINA_TIME_CLOCK_HPP
