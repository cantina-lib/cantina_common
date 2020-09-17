//
// Created by binabik on 13/09/2020.
//

#ifndef CANTINA_TILDE_UTILS_HPP
#define CANTINA_TILDE_UTILS_HPP

#pragma once

#include <cmath>
#include <algorithm>
#include <functional>

#include <cant/common/types.hpp>

#include <cant/common/macro.hpp>
CANTINA_MATHS_NAMESPACE_BEGIN

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
CANTINA_MATHS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TILDE_UTILS_HPP
