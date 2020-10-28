//
// Created by binabik on 18/07/2020.
//

#ifndef CANTINA_COMMON_MEMORY_HPP
#define CANTINA_COMMON_MEMORY_HPP

#pragma once

#include <array>
#include <list>
#include <map>
#include <memory>
#include <tuple>
#include <vector>

#include <cant/common/types.hpp>

#include <cant/common/macro.hpp>
CANTINA_CANT_NAMESPACE_BEGIN

template <class C>
using UPtr = ::std::unique_ptr<C>;

template <class C>
using ShPtr = ::std::shared_ptr<C>;

template <class C>
using WPtr = ::std::weak_ptr<C>;

template <class C>
using Stream = ::std::vector<C>;

template <class C>
using UStream = Stream<UPtr<C>>;

template <typename... Ts>
using Tuple = ::std::tuple<Ts...>;

template <typename T, size_u n_V>
using Array = ::std::array<T, n_V>;

template <class C>
using List = ::std::list<C>;

template <typename Key_T, typename Val_T>
using Map = ::std::map<Key_T, Val_T>;

template <typename T1, typename T2>
using Pair = ::std::pair<T1, T2>;

CANTINA_CANT_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_COMMON_MEMORY_HPP
