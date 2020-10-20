
#ifndef CANTINA_PHYSICS_PHYSICALPOSITION_HPP
#define CANTINA_PHYSICS_PHYSICALPOSITION_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/maths/algebra/Vector.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

    template <typename Len_T, size_u dim>
    class Positionable
    {
    public:
        /** -- typedefs -- **/
        typedef maths::Vector<Len_T, dim> Position;
        typedef maths::Vector<Len_T, dim> Vector;

        /** -- methods -- **/
        virtual ~Positionable() = default;

        virtual void setPosition(Position position) = 0;

        virtual Position const& getPosition() const = 0;

        /** -- fields -- **/

    };

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_PHYSICS_PHYSICALPOSITION_HPP