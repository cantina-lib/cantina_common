
#ifndef CANTINA_PHYSICS_COLLISIONOBJECT_HPP
#define CANTINA_PHYSICS_COLLISIONOBJECT_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/physics/PhysicalCollider.hpp>
#include <cant/physics/PhysicalShape.hpp>

#include <cant/physics/PhysicalObject.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <typename Len_T, typename Mass_T, size_u dim>
class CollisionObject : public PhysicalObjectTrait<PhysicalState<Len_T, dim>, Len_T, dim>,
                        public Collidable<Len_T, Mass_T, dim>
{
   public:
    /** -- typedef -- **/
    typedef typename Positionable<Len_T, dim>::Position        Position;
    typedef typename Kinetic<Len_T, Mass_T, dim>::Velocity     Velocity;
    typedef typename Kinetic<Len_T, Mass_T, dim>::Acceleration Acceleration;

    typedef PhysicalState<Len_T, dim>            State;
    typedef PhysicalCollider<Len_T, Mass_T, dim> Collider;
    typedef PhysicalShape<Len_T, dim>            Shape;

    /** -- methods -- **/
    CANT_EXPLICIT
    CollisionObject(UPtr<State> state, UPtr<Shape> shape);
    // applying work of forces on the object
    // and so update its state.
    // should only be called by the simulation.

    // Positionable through Collidable
    void
      setPosition(Position position) override;
    Position const &
      getPosition() const override;

    // Kinetic through Collidable
    // nothing to do here, basically.
    void setMass(Mass_T) override { CANTINA_ASSERT(false, "should not try to call this method."); }
    CANT_NODISCARD Mass_T
      getInverseMass() const override
    {
        return static_cast<Mass_T>(0);
    }
    CANT_NODISCARD Velocity const &
                   getVelocity() const override
    {
        return c_staticVelocity;
    }
    void           setVelocity(Velocity) override { CANTINA_ASSERT(false, "should not try to call this method."); }
    CANT_NODISCARD Acceleration const &
                   getAcceleration() const override
    {
        return c_staticAcceleration;
    }

    // Collidable
    WPtr<Collider>
      getCollider() const override;
    CANT_NODISCARD bool
      isStatic() const override
    {
        return true;
    }

   private:
    /** -- methods -- **/

    /** -- fields -- **/
    ShPtr<Collider> m_collider;

    Stream<WPtr<Collider>> m_inContactColliders;

    CANT_CONSTEXPR static Velocity c_staticVelocity     = Velocity();
    CANT_CONSTEXPR static Velocity c_staticAcceleration = Acceleration();
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/CollisionObject.inl>

#endif  // CANTINA_PHYSICS_COLLISIONOBJECT_HPP
