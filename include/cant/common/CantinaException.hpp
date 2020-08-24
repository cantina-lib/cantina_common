//
// Created by piptouque on 01/05/2020.
//

#ifndef CANTINA_CANTINAEXCEPTION_HPP
#define CANTINA_CANTINAEXCEPTION_HPP

#pragma once


#include <exception>
#include <list>
#include <string>

#include <cant/common/macro.hpp>

namespace cant
{


    struct Trace
    {
        std::string function;
        std::string file;
        int line;

        Trace(std::string function, std::string file, int line);
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
        std::string& msg();
        CANT_NODISCARD const std::string& msg() const;
    public:
        CantinaException(
                const Trace& trace,
                std::string&& msg);

        CANT_EXPLICIT CantinaException(
                const std::exception& e
                );

        CantinaException(
                const std::string& function,
                const std::string& file,
                int line,
                std::string&& msg
                );

        CANT_NODISCARD const char* what() const CANT_NOEXCEPT override;

        void addTrace(const Trace& trace);

        virtual void makeDisplayedLog() const CANT_NOEXCEPT;

    };
}


#include <cant/common/undef_macro.hpp>

#include "CantinaException.inl"

#endif //CANTINA_CANTINAEXCEPTION_HPP
