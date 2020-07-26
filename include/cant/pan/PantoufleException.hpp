//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_MIDIEXCEPTION_HPP
#define CANTINA_MIDIEXCEPTION_HPP

#pragma once

#include <cant/CantinaException.hpp>
#include <cant/macro.hpp>

#include <string>
#include <utility>
#include <iostream>

#pragma once

namespace cant::midi
{

    class MidiException : public CantinaException
    {
    public:
        MidiException(const Trace& trace, std::string&& msg)
        : CantinaException(trace, std::move(msg))
        {}

        MidiException(
                const std::string& function,
                const std::string& file,
                const int line,
                std::string&& msg)
        : CantinaException(function, file, line, std::move(msg))
        {}
    };
}

#   define PANTOUFLE_EXCEPTION(msg) MidiException(CANT_CURRENT_TRACE, msg)
#   define PANTOUFLE_TRY_RETHROW(expression) { try { expression } catch (cant::midi::MidiException& e) { e.CANTINA_EXCEPTION_ADD_TRACE(); throw; } }

#endif //CANTINA_MIDIEXCEPTION_HPP
