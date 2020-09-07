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
    typedef std::uint8_t vel_u8;
    typedef std::uint8_t tone_u8;

    typedef std::uint8_t id_u8;

    typedef type_d vel_d;
    typedef type_d tone_d;
    typedef type_d pan_d; // should be e [-1, 1]

    typedef type_d time_d;

    template<typename T>
    using timecallback_f = std::function<T(time_d)>;


    CANT_CONSTEXPR vel_u8 MIDI_MAX_VELOCITY = 127;
    CANT_CONSTEXPR tone_u8 MIDI_MAX_TONE = 127; // is it??

    CANT_CONSTEXPR id_u8  MIDI_CONTROL_MID_VALUE = 63;
}

#include <cant/common/undef_macro.hpp>

#endif //CANTINA_MIDITYPES_HPP
