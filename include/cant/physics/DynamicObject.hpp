
#ifndef CANTINA_PHYSICS_DYNAMICOBJECT_HPP
#define CANTINA_PHYSICS_DYNAMICOBJECT_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/physics/KineticObject.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T> class RigidObject;

template <size_u dim, typename T>
class DynamicObject : public KineticObject<dim, T>
{
    /** -- contraints -- **/
    static_assert(std::is_arithmetic_v<T>);
    // static_assert(std::is_floating_point_v<T>); ?

   public:
    /** -- typedefs -- **/
    typedef typename Positionable<dim, T>::Position    Position;
    typedef typename Positionable<dim, T>::Vector      Vector;

    // Where we will store the accumulated force
    struct KineticBuffer
    {
        Vector deltaForce;
    };

    /** -- methods -- **/
    DynamicObject(T mass, Position position, Vector velocity);
    DynamicObject(T mass, Position position);
    CANT_EXPLICIT DynamicObject(T mass);

    void translate(Vector const & vec);

    // Positionable
    void setPosition(Position pos) override;
    Position const & getPosition() const override;
    // implemented from Movable
    void
      setMass(T mass) override;
    CANT_NODISCARD T
      getInverseMass() const override;
    void
                   setVelocity(Vector velocity) override;
    CANT_NODISCARD Vector
                   getVelocity() const override;
    CANT_NODISCARD Vector
                   getAcceleration() const override;

    // makes sense for them to be final for now.
    // remove that when necessary.
    void
    addDeltaForce(Vector const & dF) final;

   private:
    /** -- methods -- **/
    void
    updateVelocity(T dt) final;
    void
    updatePosition(T dt) final;
    void
    clearForceBuffer() final;

    /** -- fields -- **/
    T m_inverseMass;

    Position m_position;
    Vector      m_velocity;
    KineticBuffer m_forceBuffer;
    // last value of acceleration, computed from last force buffer.
    // should not be used inside this class, but can exposed to the public.
    Vector m_accelerationCache;

    /** -- friend classes -- **/
    // in order delegate this stuff.
    friend class RigidObject<dim, T>;
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/DynamicObject.inl>

#endif  // CANTINA_PHYSICS_DYNAMICOBJECT_HPP
