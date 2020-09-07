//
// Created by binabik on 07/09/2020.
//

#ifndef CANTINA_TILDE_INTERPOLATION_INL
#define CANTINA_TILDE_INTERPOLATION_INL

#pragma once

#include <cant/common/types.hpp>

#include <cant/common/macro.hpp>
namespace cant::maths
{

    template<typename Ret_T, typename... Param_Ts>
    InterpolationOneD<Ret_T, Param_Ts...>::InterpolationOneD(
            std::initializer_list<InterpolationPoint<Ret_T, Param_Ts...>> il)
    : m_values(il)
            {}

    template<typename Ret_T, typename... Param_Ts>
    InterpolationOneD<Ret_T, Param_Ts...>::InterpolationOneD(const InterpolationOneD::Values &values)
            : m_values(values)
    {
        static_assert(std::is_arithmetic<Param_Ts...>::value);
    }

    template<typename Ret_T, typename... Param_Ts>
    Ret_T BrokenLinesInterpolation<Ret_T, Param_Ts...>::operator()(const Param_Ts &... args) const
    {

    }
}
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TILDE_INTERPOLATION_INL
