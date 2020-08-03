//
// Created by piptouque on 29/04/2020.
//

#ifndef CANTINA_TIME_HPP
#define CANTINA_TIME_HPP

#pragma once

#include <chrono>

#include <cant/common/macro.hpp>

#include <cant/pan/common/PantoufleException.hpp>
#include <cant/pan/common/types.hpp>

namespace cant::pan
{
    class MidiMoment
    {
    private:
        int_m _val;
    public:
        CANT_CONSTEXPR MidiMoment() : MidiMoment(0) { }
        CANT_CONSTEXPR MidiMoment(int_m val) : _val(val) { }
        void next();

        CANT_NODISCARD int_m getValue() const;

        CANT_NODISCARD bool operator==(const MidiMoment& moment) const;
        CANT_NODISCARD bool operator!=(const MidiMoment& moment) const;

        CANT_NODISCARD bool operator<=(const MidiMoment& moment) const;
        CANT_NODISCARD bool operator>(const MidiMoment& moment) const;

        CANT_NODISCARD bool operator>=(const MidiMoment& moment) const;
        CANT_NODISCARD bool operator<(const MidiMoment& moment) const;
    };

    class MidiMomentDelta
    {
    private:
        MidiMoment _t1, _t2;

    public:
        MidiMomentDelta();
        MidiMomentDelta(const MidiMoment& t1, const MidiMoment& t2)
        : _t1(t1), _t2(t2)
        {

        }

        CANT_NODISCARD int_m getDelta() const;
    };

    class MidiTimer
    {
    private:
       static std::chrono::time_point<std::chrono::steady_clock> _mainTStart;
       MidiMoment _moment;
    public:
       MidiTimer();

       void update();

       CANT_NODISCARD time_m getCurrentTime() const;
    };
}

#endif //CANTINA_TIME_HPP
