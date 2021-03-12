//
// Created by binabik on 12/03/2021.
//

#ifndef CANTINA_MATHS_ALGO_HPP
#define CANTINA_MATHS_ALGO_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/common/CantinaException.hpp>

#include <cant/common/macro.hpp>
CANTINA_MATHS_NAMESPACE_BEGIN

// in lower case to pretend it's a namespace
// although the template arguments kind of give it away.
template <typename T>
class algo
{
   public:
    /** -- methods -- **/

    template <type_i order, typename InputIt>
    CANT_NODISCARD CANT_CONSTEXPR static T
      norm(InputIt first, InputIt last);

    template <type_i order>
    CANT_NODISCARD CANT_CONSTEXPR static T power(T val);

};

CANTINA_MATHS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/maths/algo.inl>

#endif  // CANTINA_MATHS_ALGO_HPP
