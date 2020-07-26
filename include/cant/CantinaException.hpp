//
// Created by piptouque on 01/05/2020.
//

#ifndef CANTINA_CANTINAEXCEPTION_HPP
#define CANTINA_CANTINAEXCEPTION_HPP

#pragma once


#include <exception>
#include <list>
#include <sstream>

#include <cant/formatting.hpp>
#include <cant/macro.hpp>

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
                sstream << fmt::format("By {0}, in {1}, line {2}__", trace.function, trace.file, trace.line);
                sstream << std::endl;
            }
            sstream << "With message: " << _msg << std::endl;
            _displayedLog = sstream.str();
        }

    };
}

#   define CANT_CURRENT_TRACE cant::Trace(CANT_CURRENT_FUNC, CANT_CURRENT_FILE, CANT_CURRENT_LINE)
#   define CANTINA_EXCEPTION_ADD_TRACE() _addTrace_(CANT_CURRENT_TRACE)

#   define CANTINA_EXCEPTION(msg) CantinaException(CANT_CURRENT_TRACE, msg)
/*
 * todo: should it be internal? In that case, remove namespace specifier.
 */
#   define CANTINA_TRY_RETHROW(expression) { \
                                                 try { \
                                                    expression \
                                                    } \
                                                    catch(CantinaException& e) { \
                                                        e.CANTINA_EXCEPTION_ADD_TRACE(); \
                                                    } \
                                                    catch(const std::exception& e) \
                                                    { \
                                                        throw CantinaException(e); \
                                                    } \
                                             } \

#endif //CANTINA_CANTINAEXCEPTION_HPP
