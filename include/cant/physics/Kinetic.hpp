
#ifndef CANTINA_PHYSICS_KINETIC_HPP
#define CANTINA_PHYSICS_KINETIC_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/physics/Positionable.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <typename Len_T, typename Mass_T, size_u dim>
class Kinetic
{
   public:
    /** -- typedefs -- **/
    typedef typename Positionable<Len_T, dim>::Position Position;
    typedef Position                                    Velocity;
    typedef Position                                    Acceleration;

    /** -- methods -- **/
    virtual ~Kinetic() = default;

    virtual void
      setMass(Mass_T mass)
      = 0;
    CANT_NODISCARD virtual Mass_T
      getInverseMass() const = 0;

    /*
     * IMPORTANT
     * Only collision processes should
     * set the velocity and acceleration by hand
     * it should otherwise be updated with the acceleration.
     */
    virtual void
      setVelocity(Velocity velocity)
      = 0;
    CANT_NODISCARD virtual Velocity const &
      getVelocity() const = 0;

    CANT_NODISCARD virtual Acceleration const &
      getAcceleration() const = 0;
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_KINETIC_HPP