//
// Created by binabik on 18/07/2020.
//

#ifndef CANTINA_MEM_MNGMNT_HPP
#define CANTINA_MEM_MNGMNT_HPP

#pragma once

#include <map>
#include <vector>
#include <tuple>
#include <array>
#include <memory>

#include <cant/common/types.hpp>

#include <cant/common/macro.hpp>
CANTINA_CANT_NAMESPACE_BEGIN

    template<class C>
    using UPtr  = ::std::unique_ptr<C>;

    template<class C>
    using Stream = ::std::vector<C>;

    template<class C>
    using UStream = Stream<UPtr<C>>;

    template <typename... Ts>
    using Tuple = ::std::tuple<Ts...>;

    template <typename T, size_u n_V>
    using Array = ::std::array<T, n_V>;

    template <typename Key_T, typename Val_T>
    using Map = ::std::map<Key_T, Val_T>;

CANTINA_CANT_NAMESPACE_END
#include <cant/common/undef_macro.hpp>


#endif //CANTINA_MEM_MNGMNT_HPP
