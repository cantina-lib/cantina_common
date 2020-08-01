//
// Created by binabik on 05/06/2020.
//

#ifndef CANTINA_CLONEABLE_HPP
#define CANTINA_CLONEABLE_HPP

#pragma once

#include <cant/common/macro.hpp>
#include <cant/common/types.hpp>

#include <cant/common/memory.hpp>

#include <cant/pan/common/PantoufleException.hpp>

namespace cant::pan
{
    /*
     * important: Cloneable should be inherited as private
     * todo: why again??? cant remember!
     */
    template<typename C>
    class Cloneable
    {
    private:
        CANT_NODISCARD virtual UPtr<C> IMPL_clone() const = 0;
    public:
        CANT_NODISCARD virtual UPtr<C> clone() const
        {
            PANTOUFLE_TRY_RETHROW({
                 return UPtr<C>(IMPL_clone());
            })
        }
    };
}

#endif //CANTINA_CLONEABLE_HPP
