
#ifndef CANTINA_TIME_INTERNALTIME_HPP
#define CANTINA_TIME_INTERNALTIME_HPP

#pragma once

#include <cant/common/memory.hpp>

#include <cant/time/Clock.hpp>

#include <cant/common/macro.hpp>

CANTINA_TIME_NAMESPACE_BEGIN
/*
 * decorator for Clock that can be stopped
 * and keeps its own internal time reckoning base on another clock.
 */
class InternalClock : public Clock
{
   public:
    /** -- typedefs -- **/
    /** -- methods -- **/
    CANT_NODISCARD static UPtr<InternalClock>
      make(UPtr<ExternalClock> externalClock);

    void
      setCustomTimeGetter(time::AbsoluteTimeGetter absoluteTimeGetter);

    void
      start();
    void
      stop();
    void
      update();

    void
      reset();

    CANT_NODISCARD bool
      isRunning() const;

    /** -- fields -- **/

    void
      updateTime() override;

   private:
    /** -- methods -- **/
    CANT_EXPLICIT
    InternalClock(UPtr<ExternalClock> externalClock);

    // private inheritance
    // Contrarily to Clock, this is Cantina internal time
    // So that it stops when this clock is not updated.
    CANT_NODISCARD type_d
      getCurrentTimeSeconds() const override;
    CANT_NODISCARD type_d
      getDeltaTimeSeconds() const override;

    /** -- fields -- **/
    UPtr<ExternalClock> m_externalClock;

    time_d m_tStartAbsoluteExternal;

    time_d m_tStartRunningExternal;
    time_d m_tStopRunningExternal;

    time_d m_tLastInternal;

    time_d m_tNotRunningTotal;
    bool   m_isRunning;
};

CANTINA_TIME_NAMESPACE_END

#include <cant/common/undef_macro.hpp>

#include <cant/time/InternalClock.inl>

#endif  // CANTINA_TIME_INTERNALTIME_HPP