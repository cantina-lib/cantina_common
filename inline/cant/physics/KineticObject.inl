
#ifndef CANTINA_PHYSICS_KINETICOBJECT_INL
#define CANTINA_PHYSICS_KINETICOBJECT_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
KineticObject<dim, T>::KineticObject(T mass, Position position, Vector velocity)
        : PhysicalObject<dim, T>(std::move(position)),
          m_inverseMass(), m_velocity(), m_forceBuffer(), m_accelerationCache()
{
    setMass(mass);
    setVelocity(std::move(velocity));
}

template <size_u dim, typename T>
KineticObject<dim, T>::KineticObject(T mass, Position position)
    : KineticObject(mass, std::move(position), Vector())
{ }

template <size_u dim, typename T>
KineticObject<dim, T>::KineticObject(T mass) : KineticObject(mass, Position())
{}

template <size_u dim, typename T>
CANT_INLINE void
  KineticObject<dim, T>::addDeltaForce(const Vector & dF)
{
    m_forceBuffer.deltaForce += dF;
}

template <size_u dim, typename T>
CANT_INLINE void
  KineticObject<dim, T>::updateVelocity(T dt)
{
    // Hypothesis:
    // 1) intertial frame of reference (okay)
    // 2) constant mass
    //         a(t)      = F(t) / mass
    //         da        = dF   / mass
    //         a(t + dt) = a(t)  + dF / mass
    Vector dF = m_forceBuffer.deltaForce;
    m_accelerationCache = dF * getInverseMass();
    //         v(t + dt) = v(t) + dv(t)
    // with:     dv(t) = a(t) * dt
    // hence:  v(t + dt) = v(t) + a(t) * dt
    m_velocity += m_accelerationCache * dt;
}

template <size_u dim, typename T>
CANT_INLINE void
  KineticObject<dim, T>::updatePosition(T dt)
{
    // (p(t + dt) - p(t)) / dt = v(t)
    // so: p(t + dt) = p(t) + v(t) * dt
    this->translate(m_velocity * dt);
}

template <size_u dim, typename T>
CANT_INLINE void
  KineticObject<dim, T>::clearForceBuffer()
{
    m_forceBuffer.deltaForce = Vector();
}

template <size_u dim, typename T>
void
  KineticObject<dim, T>::setMass(T mass)
{
    // if the mass is null, the object will be static.
    bool const isStatic = mass == static_cast<T>(0.0);
    this->template raiseFlags(FObjectBehaviour::fStaticObject, isStatic);
    m_inverseMass = isStatic ? static_cast<T>(0) : static_cast<T>(1.0) / mass;
    // Now, let's pretend this did not happen and that the
    // constant mass hypothesis still stands, so that we can use:
    // dP = d(mass * velocity) = mass * dvelocity
}

template <size_u dim, typename T>
CANT_INLINE typename KineticObject<dim, T>::Vector const &
  KineticObject<dim, T>::getVelocity() const
{
    return m_velocity;
}

template <size_u dim, typename T>
CANT_INLINE void
KineticObject<dim, T>::setVelocity(Vector velocity)
{
    m_velocity = std::move(velocity);
}

template <size_u dim, typename T>
T
  KineticObject<dim, T>::getInverseMass() const
{
    return m_inverseMass;
}

template <size_u dim, typename T>
CANT_INLINE typename KineticObject<dim, T>::Vector
  KineticObject<dim, T>::getAcceleration() const
{
    return m_accelerationCache;
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_KINETICOBJECT_INL
