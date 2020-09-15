//
// Created by binabik on 24/08/2020.
//

#ifndef CANTINA_TILDE_CANTINAEXCEPTION_INCL_H
#define CANTINA_TILDE_CANTINAEXCEPTION_INCL_H

#pragma once

#include <cant/common/formatting.hpp>

#include <cant/common/macro.hpp>
namespace cant
{

    CANT_INLINE std::string& CantinaException::msg()                            { return m_msg; }
    CANT_NODISCARD CANT_INLINE const std::string& CantinaException::msg() const { return m_msg; }

    CANT_NODISCARD CANT_INLINE const char* CantinaException::what() const CANT_NOEXCEPT
{
        makeDisplayedLog();
        return m_displayedLog.c_str();
    }

    CANT_INLINE void CantinaException::addTrace(const Trace &trace)
    {
        m_traces.push_front(trace);
    }

}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_TILDE_CANTINAEXCEPTION_INCL_H
