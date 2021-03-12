
#ifndef CANTINA_MATHS_ALGO_INL
#define CANTINA_MATHS_ALGO_INL

#pragma once

#include <algorithm>
#include <cmath>
#include <limits>

#include <cant/common/macro.hpp>
CANTINA_MATHS_NAMESPACE_BEGIN

template <typename T>
template <type_i order, typename InputIt>
CANT_CONSTEXPR T
algo<T>::norm(InputIt first, InputIt last)
{
    static_assert(order >= 0, "Order must be positive or null!");
    if constexpr (order == 0)
    {
        // L-inf norm
        return *std::max_element(first, last);
    }
    else
    {
        return std::pow(
          std::accumulate(first, last,
                             static_cast<T>(0.),
                     [](T const & acc, T const & el) {
                              return acc + power<order>(el);
                                }
                            ), 1.0 / order);
    }
}

template <typename T>
template <type_i order>
constexpr T
algo<T>::power(T val)
{
    static_assert(order >= 0, "nooo");
    if constexpr (order == 0)
    {
        return static_cast<T>(1);
    }
    else if constexpr (order % 2 == 0)
    {
        val = power<order / 2>(val);
        return val * val;
    }
    else
    {
        return power<order - 1>(val) * val;
    }
}
CANTINA_MATHS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_MATHS_ALGO_INL