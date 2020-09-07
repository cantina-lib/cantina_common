//
// Created by binabik on 09/08/2020.
//

#ifndef CANTINA_TILDE_MATHS_HPP
#define CANTINA_TILDE_MATHS_HPP

#pragma once

#include <cmath>
#include <functional>

#include <cant/common/types.hpp>

#include <cant/common/macro.hpp>

namespace cant::maths
{
    template <typename Ret_T, typename Val_T>
    using interpolfunc_m = std::function<Ret_T(const Val_T& val1, const Val_T& val2)>;

    template <typename T>
    CANT_CONSTEXPR T barycentre(const T& a, const T& b, type_d lambda)
    {
        CANTINA_ASSERT(
                (lambda >= static_cast<type_d>(0.))
                && (lambda <= static_cast<type_d>(1.)),
                "Lambda out of range."
        );
        return a * (static_cast<type_d>(1.) - lambda) + b * lambda;
    }



}

#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TILDE_MATHS_HPP
