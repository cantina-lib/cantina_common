
#ifndef CANTINA_PHYSICS_RIGIDBODY_HPP
#define CANTINA_PHYSICS_RIGIDBODY_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/common/types.hpp>

#include <cant/physics/KineticObject.hpp>
#include <cant/physics/DynamicObject.hpp>

#include <cant/physics/PhysicalCollider.hpp>
#include <cant/physics/PhysicalShape.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
class RigidObject : public KineticObject<dim, T>, public Collidable<dim, T>
{
   public:
    /** -- typedef -- **/
    typedef PhysicalShape<dim, T>    Shape;
    typedef PhysicalCollider<dim, T> Collider;
    typedef KineticObject<dim, T>      Kinetic;
    typedef DynamicObject<dim, T>      Dynamic;
    typedef typename Kinetic::Position Position;
    typedef typename Kinetic::Vector Vector;

    /** -- methods -- **/
    RigidObject(UPtr<Kinetic> object, ShPtr<Shape> shape);

    // Collidable
    CANT_NODISCARD CANT_INLINE WPtr<Collider> getCollider() const override;
    CANT_NODISCARD CANT_INLINE bool isStatic() const override;

    // Movable
    CANT_INLINE void setMass(T mass) final;
    CANT_NODISCARD CANT_INLINE T getInverseMass() const final;
    CANT_INLINE void setVelocity(Vector velocity) final;
    CANT_NODISCARD CANT_INLINE Vector getVelocity() const final;
    CANT_NODISCARD CANT_INLINE Vector getAcceleration() const final;
    CANT_INLINE void addDeltaForce(Vector const & dF) final;

    // Positionable
    CANT_INLINE void setPosition(Position position) override;
    CANT_NODISCARD CANT_INLINE Position const & getPosition() const override;

    //Physical Object
    CANT_NODISCARD CANT_INLINE ObjectBehaviourFlags getFlags() const override;
    CANT_NODISCARD CANT_INLINE bool hasFlag(FObjectBehaviour flag) const override;
    CANT_INLINE void raiseFlags(ObjectBehaviourFlags flag, bool add) override;
    CANT_INLINE void resetFlags(ObjectBehaviourFlags flags) override;

   private:
    /** -- methods -- **/
    // Movable
    CANT_INLINE void updateVelocity(T dt) final;
    CANT_INLINE void updatePosition(T dt) final;
    CANT_INLINE void clearForceBuffer() final;

    /** -- fields -- **/
    UPtr<Kinetic> m_object;
    ShPtr<Collider> m_collider;

    Stream<WPtr<Collider>> m_inContactColliders;
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/RigidObject.inl>

#endif  // CANTINA_PHYSICS_RIGIDBODY_HPP
