
#ifndef CANTINA_COMMON_TRAITS_HPP
#define CANTINA_COMMON_TRAITS_HPP

#pragma once

#include <type_traits>

#include <cant/common/macro.hpp>
CANTINA_CANT_NAMESPACE_BEGIN

template <typename T>
using LRef = typename std::add_lvalue_reference<T>::type;

CANTINA_CANT_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_COMMON_TRAITS_HPP