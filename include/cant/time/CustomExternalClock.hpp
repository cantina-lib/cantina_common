//
// Created by binabik on 17/09/2020.
//

#ifndef CANTINA_TIME_CUSTOMCLOCK_HPP
#define CANTINA_TIME_CUSTOMCLOCK_HPP

#pragma once

#include <cant/time/Clock.hpp>

#include <cant/common/macro.hpp>
CANTINA_TIME_NAMESPACE_BEGIN

class CustomExternalClock : public ExternalClock
{
   public:
    /** -- methods -- **/
    // factory method
    CANT_NODISCARD static UPtr<ExternalClock>
      make(AbsoluteTimeGetter absoluteTimeGetter);

    void
      updateTime() override;

   private:
    /** -- methods -- **/
    CANT_EXPLICIT
    CustomExternalClock(AbsoluteTimeGetter absoluteTimeGetter);

    CANT_NODISCARD type_d
      getCurrentTimeSeconds() const override;
    CANT_NODISCARD type_d
      getDeltaTimeSeconds() const override;

    /** -- fields -- **/
    AbsoluteTimeGetter m_absoluteTimeGetter;
    time_d             m_tStart;
    time_d             m_tAbsolute;
    time_d             m_tLast;
};

CANTINA_TIME_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/time/CustomExternalClock.inl>

#endif  // CANTINA_TIME_CUSTOMCLOCK_HPP
