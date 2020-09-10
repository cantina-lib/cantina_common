//
// Created by binabik on 24/08/2020.
//

#include <cant/common/CantinaException.hpp>

#include <cant/common/formatting.hpp>

#include <cant/common/macro.hpp>
namespace cant
{

    Trace::
    Trace(std::string a_function, std::string a_file, int a_line)
            : function(std::move(a_function)), file(std::move(a_file)), line(a_line)
    {}

    CantinaException::
    CantinaException(const Trace &trace, std::string &&msg)
    : m_traces(), m_msg(std::move(msg))
    {
        addTrace(trace);
    }

    CantinaException::
    CantinaException(const std::exception &e)
            : m_traces(), m_msg(e.what())
    {

    }

    CantinaException::
    CantinaException(const std::string &function, const std::string &file, const int line,
                                       std::string &&msg)
            : CantinaException(Trace(function, file, line), std::move(msg))
    {}

    void
    CantinaException::
    makeDisplayedLog() const CANT_NOEXCEPT
    {
        /*
         * the fewer the operations
         * the less risk to throw an exception.
         * hum.
         * By the way:
         */
        std::stringstream sstream;
        sstream << "[CANTINA_EXCEPTION] ";
        for(const auto& trace : m_traces)
        {
            sstream << "By " << trace.function
                    << ", in file " << trace.file
                    << ", line " << trace.line
                    << "__";
            sstream << std::endl;
        }
        sstream << "With message: " << m_msg << std::endl;
        m_displayedLog = sstream.str();
    }
}