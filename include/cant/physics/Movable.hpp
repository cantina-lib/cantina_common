
#ifndef CANTINA_PHYSICS_MOVABLE_HPP
#define CANTINA_PHYSICS_MOVABLE_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/physics/Positionable.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T> class KineticUpdater;

template <size_u dim, typename T>
class Movable : public Positionable<dim, T>
{
   public:
    /** -- typedefs -- **/
    typedef typename Positionable<dim, T>::Position Position;
    typedef typename Positionable<dim, T>::Vector Vector;

    /** -- methods -- **/
    virtual ~Movable() = default;

    CANT_INLINE virtual void
      setMass(T mass) = 0;
    CANT_NODISCARD CANT_INLINE virtual T
      getInverseMass() const = 0;

    /*
     * IMPORTANT
     * Only collision processes should
     * set the velocity and acceleration by hand
     * it should otherwise be updated with the acceleration.
     */
    CANT_INLINE virtual void
      setVelocity(Vector velocity)
      = 0;
    CANT_NODISCARD CANT_INLINE virtual Vector const &
      getVelocity() const = 0;

    CANT_NODISCARD virtual Vector
      getAcceleration() const = 0;

    virtual void addDeltaForce(Vector const & dF) = 0;

    // these should only be called by the KineticUpdater.
    virtual void updateVelocity(T dt) = 0;
    virtual void updatePosition(T dt) = 0;
    virtual void clearForceBuffer() = 0;
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_MOVABLE_HPP