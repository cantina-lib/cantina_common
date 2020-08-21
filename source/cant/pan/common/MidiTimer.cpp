//
// Created by piptouque on 30/04/2020.
//

#include <cant/pan/common/MidiTimer.hpp>

namespace cant::pan
{
    std::chrono::time_point<std::chrono::steady_clock> MidiTimer::_mainTStart = std::chrono::steady_clock::now();

    MidiTimer::
    MidiTimer() = default;

    void
    MidiTimer::
    update()
    {
    }

    time_m
    MidiTimer::
    getCurrentTime() const
    {
        auto t = std::chrono::steady_clock::now();
        std::chrono::duration<time_m> dur = t - _mainTStart;
        return dur.count() * 1000;
    }

}
