
#ifndef CANTINA_PHYSICS_RIGIDBODY_HPP
#define CANTINA_PHYSICS_RIGIDBODY_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/common/types.hpp>

#include <cant/physics/KineticObject.hpp>

#include <cant/physics/PhysicalCollider.hpp>
#include <cant/physics/PhysicalShape.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
class Rigidbody : public Movable<dim, T>, public Collidable<dim, T>
{
   public:
    /** -- typedef -- **/
    typedef PhysicalShape<dim, T>    Shape;
    typedef PhysicalCollider<dim, T> Collider;
    typedef KineticObject<dim, T> Object;
    typedef typename Object::Vector Vector;

    /** -- methods -- **/
    Rigidbody(UPtr<Object> object, UPtr<Shape> shape);

    // Collidable
    WPtr<Collider>
      getCollider() const override;
    CANT_NODISCARD bool
      isStatic() const override
    {
        return false;
    }

    // Kinetic
    void setMass(T mass) override;
    CANT_NODISCARD T getInverseMass() const override;

    void setVelocity(Vector velocity) override;
    CANT_NODISCARD Vector const & getVelocity() const override;

    CANT_NODISCARD Vector getAcceleration() const override;

   private:
    /** -- fields -- **/
    UPtr<Object> m_object;
    ShPtr<Collider> m_collider;

    Stream<WPtr<Collider>> m_inContactColliders;
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/Rigidbody.inl>

#endif  // CANTINA_PHYSICS_RIGIDBODY_HPP
