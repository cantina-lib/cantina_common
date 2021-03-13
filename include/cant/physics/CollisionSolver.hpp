
#ifndef CANTINA_PHYSICS_COLLISIONSOLVER_HPP
#define CANTINA_PHYSICS_COLLISIONSOLVER_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/physics/PhysicalCollider.hpp>
#include <cant/physics/PhysicalCollision.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
class CollisionSolver
{
   public:
    /** -- typedefs -- **/
    typedef PhysicalCollider<dim, T>  Collider;
    typedef PhysicalCollision<dim, T> Collision;
    typedef typename PhysicalCollision<dim, T>::Position Position;
    typedef typename PhysicalCollision<dim, T>::Vector Vector;

    /** -- methods -- **/
    void
      solveCollisions(Stream<Collision> & collisions) const;
   private:
    /** -- methods -- **/
    void separateColliders(Collision & collision) const;
    void
    setCollisionVelocities(Collision & collision) const;
    void
    setCollisionSupport(Collision & collision) const;

};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/CollisionSolver.inl>

#endif  // CANTINA_PHYSICS_COLLISIONSOLVER_HPP