
#ifndef CANTINA_PHYSICS_KINETICOBJECT_HPP
#define CANTINA_PHYSICS_KINETICOBJECT_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/physics/Movable.hpp>
#include <cant/physics/PhysicalObject.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T> class KineticUpdater;

template <size_u dim, typename T>
class KineticObject : public PhysicalObject<dim, T>, public Movable<dim, T>
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
    KineticObject(T mass, Position position, Vector velocity);
    KineticObject(T mass, Position position);
    CANT_EXPLICIT KineticObject(T mass);

    // implemented from Kinetic
    void
      setMass(T mass) override;
    CANT_NODISCARD T
      getInverseMass() const override;
    void
                   setVelocity(Vector velocity) override;
    CANT_NODISCARD Vector const &
                   getVelocity() const override;
    CANT_NODISCARD Vector
                   getAcceleration() const override;

    void
    addDeltaForce(Vector const & dF);

   private:
    /** -- methods -- **/
    // these should only be called by the KineticUpdater.
    void
    updateVelocity(T dt);
    void
    updatePosition(T dt);
    void
    clearForceBuffer();



    /** -- fields -- **/
    T m_inverseMass;

    Vector      m_velocity;
    KineticBuffer m_forceBuffer;
    // last value of acceleration, computed from last force buffer.
    // should not be used inside this class, but can exposed to the public.
    Vector m_accelerationCache;

    /** -- friend classes -- **/
    // in order to call update functions:
    friend class KineticUpdater<dim, T>;
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/KineticObject.inl>

#endif  // CANTINA_PHYSICS_KINETICOBJECT_HPP
