
#ifndef CANTINA_PHYSICS_PHYSICALPOSITION_HPP
#define CANTINA_PHYSICS_PHYSICALPOSITION_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/maths/algebra/Vector.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
class Positionable
{
   public:
    /** -- typedefs -- **/
    typedef maths::Vector<dim, T> Position;
    typedef maths::Vector<dim, T> Vector;

    /** -- methods -- **/
    virtual ~Positionable() = default;

    virtual void setPosition(Position position) = 0;
    CANT_NODISCARD virtual Position const & getPosition() const = 0;

};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICALPOSITION_HPP