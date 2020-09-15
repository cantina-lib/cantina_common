//
// Created by binabik on 13/09/2020.
//

#ifndef CANTINA_TILDE_BROKENLINESINTERPOLATION_INL
#define CANTINA_TILDE_BROKENLINESINTERPOLATION_INL

#pragma once

#include <cant/maths/polynomial/PackedPolynomial.hpp>

#include <cant/common/macro.hpp>
namespace cant::maths
{

    template<typename Ret_T, typename... Param_Ts>
    BrokenLinesInterpolation<Ret_T, Param_Ts...>::
    BrokenLinesInterpolation(const typename InterpolationOneD<Ret_T, Param_Ts...>::Values &values)
            :InterpolationOneD(values)
    {

    }

    template<typename Ret_T, typename... Param_Ts>
    Ret_T
    BrokenLinesInterpolation<Ret_T, Param_Ts...>::
    operator()(const Tuple<Param_Ts>&... args) const
    {

    }

    template<typename Ret_T, typename... Param_Ts>
    CANT_NODISCARD
    Stream<typename BrokenLinesInterpolation<Ret_T, Param_Ts...>::Line>
    BrokenLinesInterpolation<Ret_T, Param_Ts...>::
    computeLines(const Stream<typename InterpolationOneD<Ret_T, Param_Ts>::Value>& values)
    {
        for (size_u i = 0; i < values.size(); ++i)
        {
            const auto& v1 = values.at(i);
            const auto& v2 = values.at(i + 1);


        }
    }
}
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TILDE_BROKENLINESINTERPOLATION_INL
