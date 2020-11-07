
#ifndef CANTINA_MATHS_UTILS_INL
#define CANTINA_MATHS_UTILS_INL

#pragma once

#include <algorithm>
#include <cmath>
#include <limits>

#include <cant/common/macro.hpp>
CANTINA_MATHS_NAMESPACE_BEGIN

template <typename T, int ulp>
bool
  approx<T, ulp>::equal(T a, T b)
{
    static_assert(std::is_floating_point_v<T>, "type must be floating-point!");
    // see example:
    // https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
    const T dist = std::fabs(b - a);
    return dist <= approx<T, ulp>::errorMargin(a, b) || dist < std::numeric_limits<T>::min();
}

template <typename T, int ulp>
bool
  approx<T, ulp>::greater(T a, T b)
{
    return a >= b - approx<T, ulp>::errorMargin(a, b);
}

template <typename T, int ulp>
bool
  approx<T, ulp>::lower(T a, T b)
{
    return a <= b - approx<T, ulp>::errorMargin(a, b);
}

template <typename T, int ulp>
bool
  approx<T, ulp>::inRange(T a, T b, T val)
{
    const T min = std::min(a, b);
    const T max = std::max(a, b);
    return approx<T, ulp>::greater(val, min) && approx<T, ulp>::lower(val, max);
}

template <typename T, int ulp>
T
  approx<T, ulp>::errorMargin(T a, T b)
{
    return std::numeric_limits<T>::epsilon() * std::fabs(b - a) * ulp;
}

template <typename T, int ulp>
template <typename Scalar_T>
CANT_INLINE T
  approx<T, ulp>::barycentre(T a, T b, Scalar_T lambda)
{
    bool const inBounds = inRange(
      static_cast<Scalar_T>(0.),
      static_cast<Scalar_T>(1.),
      lambda);
    CANTINA_ASSERT(inBounds, "Noooo!!");
    if (!inBounds)
    {
        throw CANTINA_EXCEPTION("Lambda out of [0, 1] bounds.");
    }

    return a * (static_cast<type_d>(1.) - lambda) + b * lambda;
}

CANTINA_MATHS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_MATHS_UTILS_INL