//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_PANTOUFLEEXCEPTION_HPP
#define CANTINA_PANTOUFLEEXCEPTION_HPP

#pragma once

#include <cant/common/formatting.hpp>
#include <cant/common/CantinaException.hpp>


#include <cant/common/macro.hpp>
namespace cant::pan
{

    class MidiException : public CantinaException
    {
    public:
        /** -- methods -- **/
        MidiException(const Trace& trace, std::string&& msg);
        MidiException( const std::string& function, const std::string& file, int line, std::string&& msg);
    };
}
#include <cant/common/undef_macro.hpp>

#include "PantoufleException.inl"

#endif //CANTINA_PANTOUFLEEXCEPTION_HPP
