
#ifndef CANTINA_PHYSICS_PHYSICALCOLLIDER_HPP
#define CANTINA_PHYSICS_PHYSICALCOLLIDER_HPP

#pragma once

#include <cant/common/memory.hpp>

#include <cant/physics/Movable.hpp>
#include <cant/physics/Positionable.hpp>

#include <cant/maths/geometry/Rectangle.hpp>
#include <cant/physics/PhysicalShape.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
class Collidable;

template <size_u dim, typename T>
class PhysicalCollider : public Positionable<dim, T>
{
   public:
    /** -- typedef -- **/
    typedef typename Positionable<dim, T>::Position        Position;
    typedef typename Positionable<dim, T>::Vector          Vector;

    typedef PhysicalShape<dim, T>    Shape;
    typedef maths::Rectangle<dim, T> AABB;

    /** -- methods -- **/
    PhysicalCollider(Collidable<dim, T> * owner, UPtr<Shape> shape);

    CANT_NODISCARD bool
      intersectsAABB(ShPtr<PhysicalCollider> const & other) const;
    CANT_NODISCARD bool
      intersects(ShPtr<PhysicalCollider> const & other) const;

    // in world coordinates!!
    CANT_NODISCARD Position
      getCentre() const;
    /// Get position in world coordinates of the rim which is closest to [pos].
    CANT_NODISCARD Vector
      getVectorToClosestRim(Position const & pos) const;
    CANT_NODISCARD Vector
      getVectorToCentre(Position const & pos) const;

    CANT_NODISCARD bool
      isStatic() const;

    void
      translate(Vector const & vec);

   private:
    /** -- methods -- **/

    /** -- fields -- **/
    Collidable<dim, T> * const m_owner;
    // Could be shared!
    UPtr<Shape> m_shape;
};

template <size_u dim, typename T>
class Collidable : public Positionable<dim, T>
{
   public:
    /** -- typedefs -- **/
    typedef typename Positionable<dim, T>::Position    Position;

    typedef PhysicalCollider<dim, T> Collider;

    /** -- methods -- **/
    CANT_NODISCARD virtual WPtr<Collider>
      getCollider() const = 0;

    // is the collidable subject to movement?
    // no need to check for collision between two static colliders.
    CANT_NODISCARD virtual bool
      isStatic() const = 0;
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/PhysicalCollider.inl>

#endif  // CANTINA_PHYSICS_PHYSICALCOLLIDER_HPP