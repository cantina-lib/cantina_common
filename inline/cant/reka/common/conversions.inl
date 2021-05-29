
#ifndef CANTINA_REKA_COMMON_INL
#define CANTINA_REKA_COMMON_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_REKA_NAMESPACE_BEGIN

CANT_INLINE type_d Convertor::velocityToVolumeRatio(const pan::vel_d velocity) {
    return velocity / static_cast<type_d>(pan::c_midiMaxVelocity);
}
CANT_INLINE pan::tone_d Convertor::freqToTone(const type_d freq) {
    return 12. * std::log2(freq / c_freqA4) + c_toneA4;
}

CANTINA_REKA_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_REKA_COMMON_INL