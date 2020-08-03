//
// Created by piptouque on 30/04/2020.
//

#include <cant/pan/common/MidiTimer.hpp>

namespace cant::pan
{
    std::chrono::time_point<std::chrono::steady_clock> MidiTimer::_mainTStart = std::chrono::steady_clock::now();

    MidiTimer::
    MidiTimer()
    : _moment()
    {

    }

    void
    MidiTimer::
    update()
    {
        _moment.next();
    }

    time_m
    MidiTimer::
    getCurrentTime() const
    {
        auto t = std::chrono::steady_clock::now();
        std::chrono::duration<time_m> dur = t - _mainTStart;
        return dur.count() * 1000;
    }

    int_m
    MidiMomentDelta::
    getDelta() const
    {
        return _t2.getValue() - _t1.getValue();
    }


    int_m
    MidiMoment::
    getValue() const
    {
        return _val;
    }

    bool
    MidiMoment::
    operator==(const MidiMoment &moment) const
    {
        return moment._val == _val;
    }

    bool
    MidiMoment::
    operator!=(const MidiMoment &moment) const
    {
        return !operator==(moment);
    }

    bool MidiMoment::operator<=(const MidiMoment& moment) const
    {
        return _val <= moment._val;
    }
    bool MidiMoment::operator>(const MidiMoment& moment) const
    {
        return !operator<=(moment);
    }

    bool MidiMoment::operator>=(const MidiMoment& moment) const
    {
        return operator>(moment) || operator==(moment);
    }

    bool MidiMoment::operator<(const MidiMoment& moment) const
    {
        return !operator>=(moment);
    }

    void
    MidiMoment::
    next()
    {
        ++_val;
    }


}
