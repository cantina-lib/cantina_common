
#ifndef CANTINA_PATTERNS_SLIDER_HPP
#define CANTINA_PATTERNS_SLIDER_HPP

#pragma once


#include <cant/common/functor.hpp>
#include <cant/time/common/types.hpp>

#include <cant/common/macro.hpp>
CANTINA_PATTERN_NAMESPACE_BEGIN

template <typename Value_T, typename Scalar_T>
class Slider
{
   public:
    /** -- typedefs -- **/
    typedef Functor<Value_T(Value_T const &, Value_T const &, Scalar_T)> SliderFunc;
      
    /** -- methods -- **/
    CANT_EXPLICIT Slider(SliderFunc func);

    void updateDelta(Scalar_T dt);

    Value_T const & getValue() const;
    /**
     *
     * @param target
     * @param slidingTime
     */
    void setTarget(Value_T target, Scalar_T slidingTime);
    /**
     * Sets target without changing sliding time.
     * @param target
     */
    void setTarget(Value_T target);
    /**
     * Sets sliding time and resets advancement.
     * @param slidingTime
     */
    void setSlidingTime(Scalar_T slidingTime);

    void setSlidingSpeed(Scalar_T slidingSpeed);

    /** -- fields -- **/

   private:
    /** -- methods -- **/

    /** -- fields -- **/
    SliderFunc m_func;
    Value_T m_start;
    Value_T m_target;
    Scalar_T   m_slidingTime;

    Value_T m_valueCurrent;
    Scalar_T m_slidingCurrent;

    Scalar_T m_adv;
};

CANTINA_PATTERN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/pattern/Slider.inl>

#endif  // CANTINA_PATTERNS_SLIDER_HPP
