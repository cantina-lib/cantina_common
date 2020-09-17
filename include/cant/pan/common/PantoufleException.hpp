//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_PANTOUFLEEXCEPTION_HPP
#define CANTINA_PANTOUFLEEXCEPTION_HPP

#pragma once

#include <cant/common/formatting.hpp>
#include <cant/common/CantinaException.hpp>


#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    class PantoufleException : public CantinaException
    {
    public:
        /** -- methods -- **/
        PantoufleException(const Trace& trace, std::string&& msg);
        PantoufleException(const std::string& function, const std::string& file, int line, std::string&& msg);
    };
CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/pan/common/PantoufleException.inl>

#endif //CANTINA_PANTOUFLEEXCEPTION_HPP
