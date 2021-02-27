
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
template <typename Len_T, typename Mass_T, size_u dim>
class CollisionDetector
{
   public:
    /** -- typedefs -- **/
    typedef typename Positionable<Len_T, dim>::Position Position;
    typedef PhysicalCollider<Len_T, dim>        Collider;
    typedef PhysicalCollision<Len_T, Mass_T, dim>       Collision;

    typedef type_i LayerKey;

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