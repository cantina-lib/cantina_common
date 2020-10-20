//
// Created by binabik on 13/09/2020.
//

#ifndef CANTINA_TILDE_BROKENLINESINTERPOLATION_INL
#define CANTINA_TILDE_BROKENLINESINTERPOLATION_INL

#pragma once

#include <cant/maths/polynomial/PackedPolynomial.hpp>

#include <cant/common/macro.hpp>
CANTINA_BEGIN_MATHS_NAMESPACE

    template<typename Ret_T, typename... Param_Ts>
    BrokenLinesInterpolation<Ret_T, Param_Ts...>::
    BrokenLinesInterpolation(typename InterpolationOneD<Ret_T, Param_Ts...>::Values const& values)
            :InterpolationOneD(values)
    {

    }

    template<typename Ret_T, typename... Param_Ts>
    Ret_T
    BrokenLinesInterpolation<Ret_T, Param_Ts...>::
    operator()(Tuple<Param_Ts> const&... args) const
    {

    }

    template<typename Ret_T, typename... Param_Ts>
    CANT_NODISCARD
    Stream<typename BrokenLinesInterpolation<Ret_T, Param_Ts...>::Line>
    BrokenLinesInterpolation<Ret_T, Param_Ts...>::
    computeLines(Stream<typename InterpolationOneD<Ret_T, Param_Ts>::Value> const& values)
    {
        for (size_u i = 0; i < values.size(); ++i)
        {
            auto const& v1 = values.at(i);
            auto const& v2 = values.at(i + 1);


        }
    }

CANTINA_END_MATHS_NAMESPACE
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TILDE_BROKENLINESINTERPOLATION_INL
