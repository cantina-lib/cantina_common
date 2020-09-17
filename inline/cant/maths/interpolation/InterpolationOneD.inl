//
// Created by binabik on 13/09/2020.
//

#ifndef CANTINA_TILDE_INTERPOLATIONONED_INL
#define CANTINA_TILDE_INTERPOLATIONONED_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_BEGIN_MATHS_NAMESPACE

    template<typename Ret_T, typename... Param_Ts>
    InterpolationOneD<Ret_T, Param_Ts...>::
    InterpolationOneD( std::initializer_list<InterpolationPoint<Ret_T, Param_Ts...>> il)
        : m_values(il)
    {}

    template<typename Ret_T, typename... Param_Ts>
    InterpolationOneD<Ret_T, Param_Ts...>::
    InterpolationOneD(const Stream<InterpolationOneD::Value> &values)
            : m_values(values)
    {
        static_assert(std::is_arithmetic<Param_Ts...>::value);
    }

CANTINA_END_MATHS_NAMESPACE
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TILDE_INTERPOLATIONONED_INL
