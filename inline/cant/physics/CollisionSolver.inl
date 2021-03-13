
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
        typename Collision::ContactPhase phase = collision.getPhase();
        switch (phase)
        {
        case Collision::eEnter: setCollisionVelocities(collision); break;
        case Collision::eStay: setCollisionSupport(collision); break;
        default: break;
        }
    }
}

template <size_u dim, typename T>
void CollisionSolver<dim, T>::separateColliders(Collision & collision) const
{
    typename Collision::Intersection const & intersection = collision.getIntersection();
    auto & colMax = collision.getColliderMax();
    auto & colMin = collision.getColliderMin();
    T const radiusMax = colMax->getShape()->getRadius();
    T const radiusMin = colMin->getShape()->getRadius();

    // only moving the object with the larger velocity
    // assuming it's the one which 'collided' with the other.
    Vector const vecContactCentreToRimMax = (colMax->getCentreWorld() + intersection.direction * radiusMax) - intersection.centre;
    Vector const vecContactCentreToRimMin = (colMin->getCentreWorld() - intersection.direction * radiusMin) - intersection.centre;

    // first translation is so that centre of colMax is out of colMin
    // second is so that centre of colMin is out of colMin
    // after this, the colliders should just touch each other.
    if (colMin->isStatic())
    {
       // we only move the max collider.
        colMax->translate(vecContactCentreToRimMin - vecContactCentreToRimMax);
    }
    else
    {
        colMax->translate(-vecContactCentreToRimMax);
        colMin->translate(-vecContactCentreToRimMin);
    }
}
template <size_u dim, typename T>
void
CollisionSolver<dim, T>::setCollisionVelocities(Collision & collision) const
{
    auto & colMax = collision.getColliderMax();
    auto & colMin = collision.getColliderMin();
    typename Collision::Contact const & contact = collision.getContact();
    if (!colMin->isStatic())
    {
        colMin->setVelocity(colMin->getVelocity() - contact.n * (contact.impulse * colMin->getInverseMass()));
    }
    colMax->setVelocity(colMax->getVelocity() + contact.n * (contact.impulse * colMax->getInverseMass()));
}

template <size_u dim, typename T>
void
CollisionSolver<dim, T>::setCollisionSupport(Collision & collision) const
{
    CANT_MAYBEUNUSED typename Collision::Contact const & contact = collision.getContact();
    CANT_MAYBEUNUSED T apna = contact.n.dot(collision.getColliderMax()->getAcceleration());
    CANT_MAYBEUNUSED T apnb = -contact.n.dot(collision.getColliderMin()->getAcceleration());
}


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_COLLISIONSOLVER_INL