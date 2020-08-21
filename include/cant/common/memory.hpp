//
// Created by binabik on 18/07/2020.
//

#ifndef CANTINA_MEM_MNGMNT_H
#define CANTINA_MEM_MNGMNT_H

#pragma once

#include <map>
#include <vector>
#include <tuple>
#include <memory>

#include <cant/common/types.hpp>

namespace cant
{
    template<class C>
    using UPtr  = std::unique_ptr<C>;

    template<class C>
    using Stream = std::vector<C>;

    template <typename... Ts>
    using Tuple = std::tuple<Ts...>;

    template <typename T, size_m n_V>
    using Array = std::array<T, n_V>;

    template <typename T, size_m n_V>
    using UArray = Array<UPtr<T>, n_V>;


    template <typename Key_T, typename Val_T>
    using Map = std::map<Key_T, Val_T>;

    template <typename Key_T, typename Val_T>
    using UMap = Map<Key_T, UPtr<Val_T>>;

}

#endif //CANTINA_MEM_MNGMNT_H
