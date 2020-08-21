//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_MIDIEXCEPTION_HPP
#define CANTINA_MIDIEXCEPTION_HPP

#pragma once

#include <cant/common/formatting.hpp>
#include <cant/common/CantinaException.hpp>


#include <cant/common/macro.hpp>
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
#include <cant/common/undef_macro.hpp>


#endif //CANTINA_MIDIEXCEPTION_HPP
