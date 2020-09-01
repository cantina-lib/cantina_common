//
// Created by binabik on 01/09/2020.
//

#ifndef CANTINA_TILDE_PANTOUFLEEXCEPTION_INL
#define CANTINA_TILDE_PANTOUFLEEXCEPTION_INL

#pragma once

#include <cant/common/macro.hpp>
namespace cant::pan
{
    CANT_INLINE
    MidiException::
    MidiException(const Trace& trace, std::string&& msg)
            : CantinaException(trace, std::move(msg))
    {}

    CANT_INLINE
    MidiException::
    MidiException(
            const std::string& function,
            const std::string& file,
            const int line,
            std::string&& msg)
            : CantinaException(function, file, line, std::move(msg))
    {}

}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_TILDE_PANTOUFLEEXCEPTION_INL
