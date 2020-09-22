//
// Created by piptouque on 29/04/2020.
//

#ifndef CANTINA_TIME_SYSTEMCLOCK_HPP
#define CANTINA_TIME_SYSTEMCLOCK_HPP

#pragma once

#include <chrono>

#include <cant/time/Clock.hpp>

#include <cant/common/macro.hpp>
CANTINA_TIME_NAMESPACE_BEGIN

    class SystemExternalClock : public ExternalClock
    {
    public:
        /** -- internal structs -- **/
        typedef std::chrono::steady_clock StdClock;
        /** -- methods -- **/
        // factory method
        CANT_NODISCARD static UPtr<ExternalClock> make();

        void updateTime() override;
    private:
        /** -- methods -- **/
        SystemExternalClock();
        // private inheritance
        CANT_NODISCARD type_d getCurrentTimeSeconds() const override;
        CANT_NODISCARD type_d getDeltaTimeSeconds() const override;

        /** -- fields -- **/
        std::chrono::time_point<StdClock> m_tStart;
        std::chrono::time_point<StdClock> m_tAbsolute;
        std::chrono::time_point<StdClock> m_tLast;
    };

CANTINA_TIME_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/time/SystemExternalClock.inl>

#endif // CANTINA_TIME_SYSTEMCLOCK_HPP
