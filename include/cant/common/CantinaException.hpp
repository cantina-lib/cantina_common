//
// Created by piptouque on 01/05/2020.
//

#ifndef CANTINA_CANTINAEXCEPTION_HPP
#define CANTINA_CANTINAEXCEPTION_HPP

#pragma once


#include <exception>
#include <list>

#include <cant/common/formatting.hpp>
#include <cant/common/macro.hpp>

namespace cant
{


    struct Trace
    {
        std::string function;
        std::string file;
        int line;

        Trace(std::string function_, std::string file_, int line_)
        : function(std::move(function_)), file(std::move(file_)), line(line_)
        {}
    };

    class CantinaException : std::exception
    {
    private:
        std::list<Trace> _traces;
        std::string _msg;
        /* must be mutable in order to fill inside what() */
        mutable std::string _displayedLog;
        /*
         * todo: add levels -> one should be debug (error of architecture), another runtime
         */
    protected:
        std::string& msg() { return _msg; }
        CANT_NODISCARD const std::string& msg() const { return _msg; }
    public:
        CantinaException(
                const Trace& trace,
                std::string&& msg)
        : _traces(), _msg(std::move(msg))
        {
            _addTrace_(trace);
        }

        CANT_EXPLICIT CantinaException(
                const std::exception& e
                )
                : _traces(), _msg(e.what())
        {

        }

        CantinaException(
                const std::string& function,
                const std::string& file,
                const int line,
                std::string&& msg
                )
        : CantinaException(Trace(function, file, line), std::move(msg))
        {}

        CANT_NODISCARD const char* what() const noexcept override
        {
            makeDisplayedLog();
            return _displayedLog.c_str();
        }

        void _addTrace_(const Trace& trace)
        {
            _traces.push_front(trace);
        }

        virtual void makeDisplayedLog() const noexcept
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

    };
}


#include <cant/common/undef_macro.hpp>

#endif //CANTINA_CANTINAEXCEPTION_HPP
