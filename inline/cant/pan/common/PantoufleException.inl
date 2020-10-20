//
// Created by binabik on 01/09/2020.
//

#ifndef CANTINA_TILDE_PANTOUFLEEXCEPTION_INL
#define CANTINA_TILDE_PANTOUFLEEXCEPTION_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    CANT_INLINE
    PantoufleException::
    PantoufleException(Trace const& trace, std::string&& msg)
            : CantinaException(trace, std::move(msg))
    {}

    CANT_INLINE
    PantoufleException::
    PantoufleException(
            std::string const& function,
            std::string const& file,
            int line,
            std::string&& msg)
            : CantinaException(function, file, line, std::move(msg))
    {}

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TILDE_PANTOUFLEEXCEPTION_INL
