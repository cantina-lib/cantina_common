
#ifndef CANTINA_PATTERNS_SLIDER_INL
#define CANTINA_PATTERNS_SLIDER_INL

#pragma once

#include <cant/maths/approx.hpp>

#include <cant/common/macro.hpp>
CANTINA_PATTERNS_NAMESPACE_BEGIN

template <typename Value_T, typename Scalar_T>
Slider<Value_T, Scalar_T>::Slider(SliderFunc func)
  : m_func(std::move(func)),
      m_start(),
      m_target(),
      m_slidingTime(),
      m_slidingCurrent(),
      m_adv(static_cast<Scalar_T>(0.))
{}

template <typename Value_T, typename Scalar_T>
Value_T const &
  Slider<Value_T, Scalar_T>::getValue() const
{
    return m_valueCurrent;
}
template <typename Value_T, typename Scalar_T>
void
  Slider<Value_T, Scalar_T>::setTarget(Value_T target, Scalar_T slidingTime)
{
    setTarget(std::move(target));
    setSlidingTime(slidingTime);
}
template <typename Value_T, typename Scalar_T>
void
  Slider<Value_T, Scalar_T>::setSlidingTime(Scalar_T slidingTime)
{
    m_slidingTime = slidingTime;
    m_slidingCurrent = static_cast<Scalar_T>(0.);
}
template <typename Value_T, typename Scalar_T>
void
  Slider<Value_T, Scalar_T>::setTarget(Value_T target)
{
    m_target = std::move(target);
    m_start = m_valueCurrent;
}
template <typename Value_T, typename Scalar_T>
void
  Slider<Value_T, Scalar_T>::updateDelta(Scalar_T dt)
{
    m_slidingCurrent = std::min(m_slidingTime, m_slidingCurrent + dt);
    // m_slidingTime null or negative means a frozen slider => no advancement.
    if (!maths::approx<Scalar_T>::lower(m_slidingTime, static_cast<Scalar_T>(0.)))
    {
        m_adv = m_slidingCurrent / m_slidingTime;
        m_valueCurrent = m_func(m_start, m_target, m_adv);
    }
}

CANTINA_PATTERNS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PATTERNS_SLIDER_INL
