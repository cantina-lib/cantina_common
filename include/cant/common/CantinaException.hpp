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
CANTINA_CANT_NAMESPACE_BEGIN

    struct Trace
    {
        std::string function;
        std::string file;
        int line;

        Trace(std::string function, std::string file, int line);
    };

    class CantinaException : public std::exception
    {
    public:
        /** -- methods -- **/
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
    protected:
        /** -- methods -- **/
        std::string& msg();
        CANT_NODISCARD const std::string& msg() const;
    private:
        /** -- fields -- **/
        std::list<Trace> m_traces;
        std::string m_msg;

        // must be mutable in order to fill inside what()
        mutable std::string m_displayedLog;
    };
CANTINA_CANT_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/common/CantinaException.inl>

#endif //CANTINA_CANTINAEXCEPTION_HPP
