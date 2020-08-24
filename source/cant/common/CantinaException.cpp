//
// Created by binabik on 24/08/2020.
//

#include <cant/common/CantinaException.hpp>

#include <cant/common/formatting.hpp>

#include <cant/common/macro.hpp>
namespace cant
{

    Trace::Trace(std::string function, std::string file, int line)
            : function(std::move(function)), file(std::move(file)), line(line)
    {}

    CantinaException::CantinaException(const Trace &trace, std::string &&msg)
    : _traces(), _msg(std::move(msg))
    {
        addTrace(trace);
    }

    CantinaException::CantinaException(const std::exception &e)
            : _traces(), _msg(e.what())
    {

    }

    CantinaException::CantinaException(const std::string &function, const std::string &file, const int line,
                                       std::string &&msg)
            : CantinaException(Trace(function, file, line), std::move(msg))
    {}

    void CantinaException::makeDisplayedLog() const CANT_NOEXCEPT
    {
        /*
         * the fewer the operations
         * the less risk to throw an exception.
         * hum.
         * By the way:
         ** todo: This function should logically be noexcept, how but can we guarantee that?
         */
        std::stringstream sstream;
        sstream << "[CANTINA_EXCEPTION] ";
        for(const auto& trace : _traces)
        {
            sstream << "By " << trace.function
                    << ", in file " << trace.file
                    << ", line " << trace.line
                    << "__";
            sstream << std::endl;
        }
        sstream << "With message: " << _msg << std::endl;
        _displayedLog = sstream.str();
    }
}