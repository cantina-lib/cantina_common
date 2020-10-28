//
// Created by binabik on 01/09/2020.
//

#ifndef CANTINA_TIME_CUSTOMCLOCK_INL
#define CANTINA_TIME_CUSTOMCLOCK_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_TIME_NAMESPACE_BEGIN

CANT_INLINE
CustomExternalClock::CustomExternalClock(AbsoluteTimeGetter absoluteTimeGetter)
    : m_absoluteTimeGetter(std::move(absoluteTimeGetter)), m_tStart(m_absoluteTimeGetter()), m_tAbsolute(), m_tLast()
{}

CANT_INLINE
void
  CustomExternalClock::updateTime()
{
    m_tLast     = m_tAbsolute;
    m_tAbsolute = m_absoluteTimeGetter();
}

CANT_INLINE
type_d
  CustomExternalClock::getCurrentTimeSeconds() const
{
    return m_tAbsolute - m_tStart;
}

CANT_INLINE
type_d
  CustomExternalClock::getDeltaTimeSeconds() const
{
    return m_tAbsolute - m_tLast;
}

CANT_INLINE
UPtr<ExternalClock>
  CustomExternalClock::make(AbsoluteTimeGetter absoluteTimeGetter)
{
    return std::unique_ptr<ExternalClock>(new CustomExternalClock(std::move(absoluteTimeGetter)));
}
CANTINA_TIME_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_TIME_CUSTOMCLOCK_INL
