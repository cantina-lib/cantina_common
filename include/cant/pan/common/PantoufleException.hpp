//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_MIDIEXCEPTION_HPP
#define CANTINA_MIDIEXCEPTION_HPP

#pragma once

#include <cant/common/macro.hpp>
#include <cant/common/formatting.hpp>
#include <cant/common/CantinaException.hpp>

#pragma once

namespace cant::pan
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
#   define PANTOUFLE_TRY_RETHROW(expression) { try { expression } catch (cant::pan::MidiException& e) { e.CANTINA_EXCEPTION_ADD_TRACE(); throw; } }

#endif //CANTINA_MIDIEXCEPTION_HPP
