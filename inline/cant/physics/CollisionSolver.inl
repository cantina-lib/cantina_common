
#ifndef CANTINA_PHYSICS_COLLISIONSOLVER_INL
#define CANTINA_PHYSICS_COLLISIONSOLVER_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
void
  CollisionSolver<dim, T>::solveCollisions(Stream<Collision> & collisions) const
{
    for (auto & collision : collisions)
    {
        // displace the colliders so they no longer intersect
        separateColliders(collision);
        collision.computeCollision();
    }
}

template <size_u dim, typename T>
void
  CollisionSolver<dim, T>::separateColliders(Collision & collision) const
{
    auto & colMax = collision.getColliderMax();
    auto & colMin = collision.getColliderMin();

    // only moving the object with the larger velocity
    // assuming it's the one which 'collided' with the other.
    Position vecClosestRimMax = colMax->getVectorToClosestRim(colMin->getCentre());
    Position vecClosestRimMin = colMin->getVectorToClosestRim(colMax->getCentre());

    // first translation is so that centre of colMax is out of colMin
    // second is so that centre of colMin is out of colMin
    // after this, the colliders should just touch each other.
    colMax->translate(colMax->getVectorToCentre(colMin->getCentre()) + vecClosestRimMax - vecClosestRimMin);
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_COLLISIONSOLVER_INL