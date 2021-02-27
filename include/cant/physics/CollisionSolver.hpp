
#ifndef CANTINA_PHYSICS_COLLISIONSOLVER_HPP
#define CANTINA_PHYSICS_COLLISIONSOLVER_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/physics/PhysicalCollider.hpp>
#include <cant/physics/PhysicalCollision.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <typename Len_T, typename Mass_T, size_u dim>
class CollisionSolver
{
   public:
    /** -- typedefs -- **/
    typedef typename Positionable<Len_T, dim>::Position    Position;
    typedef typename Kinetic<Len_T, Mass_T, dim>::Velocity Velocity;

    typedef PhysicalCollider<Len_T, dim>  Collider;
    typedef PhysicalCollision<Len_T, Mass_T, dim> Collision;

    /** -- methods -- **/
    void
      solveCollisions(Stream<Collision> & collisions) const;

   private:
    /** -- methods -- **/
    void
      separateColliders(Collision & collision) const;

    /** -- fields -- **/
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/CollisionSolver.inl>

#endif  // CANTINA_PHYSICS_COLLISIONSOLVER_HPP