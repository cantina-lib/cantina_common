//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_MIDITYPES_HPP
#define CANTINA_MIDITYPES_HPP

#pragma once


#include <cstdint>
#include <functional>

#include <cant/common/types.hpp>

#include <cant/common/macro.hpp>

namespace cant::pan
{
    typedef uint8_t vel_mint;
    typedef uint8_t tone_mint;

    typedef uint8_t byte_m;

    typedef double vel_m;
    typedef double tone_m;
    typedef double pan_m; // should be e [-1, 1]

    typedef double time_m;

    template<typename T>
    using timefunc_m = std::function<T(time_m)>;


    CANT_CONSTEXPR vel_mint MIDI_MAX_VELOCITY = 127;
    CANT_CONSTEXPR tone_mint MIDI_MAX_TONE = 127; // is it??

    CANT_CONSTEXPR byte_m  MIDI_CONTROL_MID_VALUE = 63;
}

#include <cant/common/undef_macro.hpp>

#endif //CANTINA_MIDITYPES_HPP