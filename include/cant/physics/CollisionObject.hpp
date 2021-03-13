
#ifndef CANTINA_PHYSICS_COLLISIONOBJECT_HPP
#define CANTINA_PHYSICS_COLLISIONOBJECT_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/physics/PhysicalCollider.hpp>
#include <cant/physics/PhysicalShape.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
class CollisionObject : public PhysicalObject<dim, T>, public Collidable<dim, T>
{
   public:
    /** -- typedef -- **/
    typedef typename Collidable<dim, T>::Position        Position;
    typedef typename Collidable<dim, T>::Vector        Vector;

    typedef PhysicalCollider<dim, T> Collider;
    typedef PhysicalShape<dim, T>    Shape;

    /** -- methods -- **/
    CANT_EXPLICIT
    CollisionObject(ShPtr<Shape> shape);

    // Collidable
    WPtr<Collider>
      getCollider() const override;
    CANT_NODISCARD bool
      isStatic() const override { return true; }

    // Movable (this implementation does not do anything).
    void setVelocity(CANT_MAYBEUNUSED Vector velocity) override { }
    CANT_NODISCARD CANT_INLINE Vector getVelocity() const override { return Vector(); }
    CANT_NODISCARD CANT_INLINE Vector getAcceleration() const override { return Vector(); }
    void addDeltaForce(CANT_MAYBEUNUSED Vector const & dF) override { }
    CANT_INLINE void setMass(CANT_MAYBEUNUSED T mass) override { }
    CANT_NODISCARD CANT_INLINE T getInverseMass() const override { return static_cast<T>(0.0); }

   private:
    /** -- methods -- **/

    /** -- fields -- **/
    ShPtr<Collider> m_collider;

    Stream<WPtr<Collider>> m_inContactColliders;
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/CollisionObject.inl>

#endif  // CANTINA_PHYSICS_COLLISIONOBJECT_HPP
