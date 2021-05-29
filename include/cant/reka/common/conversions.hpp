
#ifndef CANTINA_REKA_COMMON_HPP
#define CANTINA_REKA_COMMON_HPP

#pragma once

#include <cant/common/macro.hpp>
CANTINA_REKA_NAMESPACE_BEGIN

class Convertor
{
   public:
    /** -- methods -- **/
    // static methods
    CANT_NODISCARD CANT_INLINE static type_d velocityToVolumeRatio(pan::vel_d velocity);
    CANT_NODISCARD CANT_INLINE static pan::tone_d freqToTone(type_d freq);

    static CANT_CONSTEXPR type_d c_freqA4        = 440.;
    static CANT_CONSTEXPR pan::tone_d c_toneA4   = 69.;
};

CANTINA_REKA_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/reka/common/conversions.inl>

#endif  // CANTINA_REKA_COMMON_HPP