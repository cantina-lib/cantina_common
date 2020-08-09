//
// Created by binabik on 02/08/2020.
//

#ifndef CANTINA_TILDE_MIDIEVENT_HPP
#define CANTINA_TILDE_MIDIEVENT_HPP

#pragma once

#include <cant/common/macro.hpp>
#include <cant/pan/common/types.hpp>

#include <cant/pan/common/MidiTimer.hpp>

namespace cant::pan
{
    /*
     * I probably won't ever use this stuff, but it looks nice, so it's staying.
     */
    template<typename T>
    class MidiEvent
    {
        using EventPredicate = std::function<bool(T)>;
    private:
        EventPredicate _pred;
        T _data;
    protected:
        void update(const T& data)
        {
            _data = T(data);
        }


        void clear()
        {
            _data = T();
        }
    public:
        CANT_EXPLICIT MidiEvent(EventPredicate pred)
        : _pred(std::move(pred)), _data()
        {

        }

        CANT_NODISCARD bool isHappening() const
        {
            return _pred(_data);
        }
    };

    class MidiMomentEvent : public MidiEvent<MidiMoment>
    {
    public:
        CANT_EXPLICIT MidiMomentEvent(const MidiMoment& length)
        : MidiEvent([length](const MidiMoment& moment)
                {
                    return moment <= length;
                })
        {

        }
    };

    class MidiMomentOneTimeEvent : public MidiMomentEvent
    {
    public:
        MidiMomentOneTimeEvent()
        : MidiMomentEvent(MidiMoment(1))
        {

        }
    };


    template <typename Data_T, class Event_C>
    class MidiEventUpdatable
    {
    public:
        virtual void updateEvent(const Data_T& data) = 0;
    };

}


#endif //CANTINA_TILDE_MIDIEVENT_HPP
