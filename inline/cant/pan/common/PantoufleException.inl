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
    PantoufleException(const Trace& trace, std::string&& msg)
            : CantinaException(trace, std::move(msg))
    {}

    CANT_INLINE
    PantoufleException::
    PantoufleException(
            const std::string& function,
            const std::string& file,
            const int line,
            std::string&& msg)
            : CantinaException(function, file, line, std::move(msg))
    {}

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TILDE_PANTOUFLEEXCEPTION_INL
