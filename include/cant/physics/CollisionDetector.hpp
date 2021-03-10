
#ifndef CANTINA_PHYSICS_COLLISIONDETECTOR_HPP
#define CANTINA_PHYSICS_COLLISIONDETECTOR_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/common/types.hpp>

#include <cant/physics/PhysicalCollider.hpp>
#include <cant/physics/PhysicalCollision.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

/*
 * Does discrete detection, that is, it will let colliders pass through each other
 * before checking if they are intersecting.
 * It requires that motion is not too large (dt small, for one), else they might not even intersect.
 */
template <size_u dim, typename T>
class CollisionDetector
{
   public:
    /** -- typedefs -- **/
    typedef typename Positionable<dim, T>::Position Position;
    typedef PhysicalCollider<dim, T>        Collider;
    typedef PhysicalCollision<dim, T>       Collision;

    typedef type_i LayerKey;
    CANT_CONSTEXPR static LayerKey c_defaultLayer = -1;

    /** -- methods -- **/
    CollisionDetector();

    void
      detectCollisions();

    Stream<Collision> &
      getCollisions();

    void
      addCollider(WPtr<Collider> collider, LayerKey layer);

   private:
    /** -- methods -- **/
    void
      detectBroadPhase();
    void
      detectNarrowPhase();

    /** -- fields -- **/
    Map<LayerKey, Stream<WPtr<Collider>>> m_colliders;

    Stream<Collision> m_collisions;
    Stream<Collision> m_previousCollisions;

    Stream<typename Collision::CollisionPair> m_broadCollisions;
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/CollisionDetector.inl>

#endif  // CANTINA_PHYSICS_COLLISIONDETECTOR_HPP