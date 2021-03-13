
#ifndef CANTINA_PHYSICS_PHYSICALCOLLIDER_HPP
#define CANTINA_PHYSICS_PHYSICALCOLLIDER_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/common/option.hpp>

#include <cant/physics/Movable.hpp>
#include <cant/physics/Positionable.hpp>

#include <cant/maths/geometry/Rectangle.hpp>
#include <cant/physics/PhysicalShape.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
class Collidable;

template <size_u dim, typename T>
class PhysicalCollider : public Movable<dim, T>
{
   public:
    /** -- typedef -- **/
    typedef typename PhysicalShape<dim, T>::Position        Position;
    typedef typename PhysicalShape<dim, T>::Vector        Vector;
    typedef typename PhysicalShape<dim, T>::Intersection  Intersection;
    typedef Collidable<dim, T> Object;

    typedef PhysicalShape<dim, T>    Shape;
    typedef maths::Rectangle<dim, T> AABB;

    /** -- methods -- **/
    PhysicalCollider(Collidable<dim, T> * owner, ShPtr<Shape> shape, Position centre = Position());

    CANT_NODISCARD CANT_INLINE bool
                   isIntersectingAABB(ShPtr<PhysicalCollider> const & other) const;
    CANT_NODISCARD CANT_INLINE Optional<Intersection>
      getIntersection(ShPtr<PhysicalCollider> const & other) const;

    // in world coordinates!!
    CANT_NODISCARD CANT_INLINE Position
      getCentreWorld() const;
    /// Get position in world coordinates of the rim which is closest to [pos].
    CANT_NODISCARD CANT_INLINE ShPtr<Shape> const &
      getShape() const;

    CANT_NODISCARD CANT_INLINE bool
      isStatic() const;

    CANT_INLINE void translate(Vector const & vec);
    CANT_INLINE void setPosition(Position position) final;
    CANT_NODISCARD CANT_INLINE Position const & getPosition() const final;
    CANT_INLINE void setVelocity(Vector velocity) final;
    CANT_NODISCARD CANT_INLINE Vector getVelocity() const final;

    CANT_NODISCARD virtual Vector
    getAcceleration() const final;
    CANT_INLINE virtual void
    setMass(T mass) final;
    CANT_NODISCARD CANT_INLINE virtual T
    getInverseMass() const final;

    void addDeltaForce(Vector const & dF) final;

   private:
    /** -- methods -- **/

    /** -- fields -- **/
    Object * const m_owner;
    // Could be shared!
    ShPtr<Shape> m_shape;
    Position m_centre; // in order coordinates.
};

template <size_u dim, typename T>
class Collidable : public Movable<dim, T>
{
   public:
    /** -- typedefs -- **/
    typedef typename Movable<dim, T>::Position    Position;
    typedef typename Movable<dim, T>::Vector    Vector;

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