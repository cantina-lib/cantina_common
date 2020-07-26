//
// Created by binabik on 18/07/2020.
//

#ifndef CANTINA_MEM_MNGMNT_H
#define CANTINA_MEM_MNGMNT_H

#pragma once

#include <map>
#include <vector>
#include <memory>

namespace cant
{
    template<class C>
    using UPtr  = std::unique_ptr<C>;

    template<class C>
    using ShPtr = std::shared_ptr<C>;

    template<class C>
    using WPtr = std::weak_ptr<C>;

    template<class C>
    using Stream = std::vector<C>;

    template <typename Key_T, typename Val_T>
    using Map = std::map<Key_T, Val_T>;
}

#endif //CANTINA_MEM_MNGMNT_H
