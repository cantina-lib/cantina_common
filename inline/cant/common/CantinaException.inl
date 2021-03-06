//
// Created by binabik on 24/08/2020.
//

#ifndef CANTINA_TILDE_CANTINAEXCEPTION_INCL_H
#define CANTINA_TILDE_CANTINAEXCEPTION_INCL_H

#pragma once

#include <cant/common/formatting.hpp>

#include <cant/common/macro.hpp>
CANTINA_CANT_NAMESPACE_BEGIN

CANT_INLINE
Trace::Trace(std::string a_function, std::string a_file, int a_line)
    : function(std::move(a_function)), file(std::move(a_file)), line(a_line)
{}

CANT_INLINE
std::string &
  CantinaException::msg()
{
    return m_msg;
}
CANT_NODISCARD CANT_INLINE std::string const &
                           CantinaException::msg() const
{
    return m_msg;
}

CANT_NODISCARD CANT_INLINE char const *
               CantinaException::what() const CANT_NOEXCEPT
{
    makeDisplayedLog();
    return m_displayedLog.c_str();
}

CANT_INLINE
void
  CantinaException::addTrace(Trace const & trace)
{
    m_traces.push_front(trace);
}

CANT_INLINE
CantinaException::CantinaException(Trace const & trace, std::string && msg) : m_traces(), m_msg(std::move(msg))
{
    addTrace(trace);
}

CANT_INLINE
CantinaException::CantinaException(std::exception const & e) : m_traces(), m_msg(e.what())
{}

CANT_INLINE
CantinaException::CantinaException(std::string const & function, std::string const & file, int line, std::string && msg)
    : CantinaException(Trace(function, file, line), std::move(msg))
{}

CANT_INLINE
void
  CantinaException::makeDisplayedLog() const CANT_NOEXCEPT
{
    /*
     * the fewer the operations
     * the less risk to throw an exception.
     * hum.
     * By the way:
     */
    std::stringstream sstream;
    sstream << "[CANTINA_EXCEPTION] ";
    for (auto const & trace : m_traces)
    {
        sstream << "By " << trace.function << ", in file " << trace.file << ", line " << trace.line << "__";
        sstream << std::endl;
    }
    sstream << "With message: " << m_msg << std::endl;
    m_displayedLog = sstream.str();
}

CANTINA_CANT_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_TILDE_CANTINAEXCEPTION_INCL_H
