
#ifndef CANTINA_PHYSICS_KINETICOBJECT_INL
#define CANTINA_PHYSICS_KINETICOBJECT_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
KineticObject<Len_T, Mass_T, Time_T, dim>::KineticObject(Mass_T mass, Position position, Velocity velocity)
        : PhysicalObject<Len_T, dim>(std::move(position)), m_inverseMass(), m_velocity(), m_acceleration(), m_buffer()
{
    setMass(mass);
    setVelocity(std::move(velocity));
}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
KineticObject<Len_T, Mass_T, Time_T, dim>::KineticObject(Mass_T mass, Position position)
    : KineticObject(mass, std::move(position), Velocity())
{ }

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
KineticObject<Len_T, Mass_T, Time_T, dim>::KineticObject(Mass_T mass) : KineticObject(mass, Position())
{}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
CANT_INLINE void
  KineticObject<Len_T, Mass_T, Time_T, dim>::addDeltaForce(DeltaForce const & dF)
{
    m_buffer.deltaForce += dF;
}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
CANT_INLINE void
  KineticObject<Len_T, Mass_T, Time_T, dim>::setAccelerationFromForceBuffer()
{
    // Hypothesis:
    // 1) intertial frame of reference (okay)
    // 2) constant mass
    //         a(t)      = F(t) / mass
    //         da        = dF   / mass
    //         a(t + dt) = a(t)  + dF / mass
    DeltaForce dF = m_buffer.deltaForce;
    dF *= getInverseMass();
    m_acceleration = dF;
}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
CANT_INLINE void
  KineticObject<Len_T, Mass_T, Time_T, dim>::updateVelocity(Time_T dt)
{
    //         v(t + dt) = v(t) + dv(t)
    // with:     dv(t) = a(t) * dt
    // hence:  v(t + dt) = v(t) + a(t) * dt
    m_velocity += m_acceleration * dt;
}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
CANT_INLINE void
  KineticObject<Len_T, Mass_T, Time_T, dim>::updatePosition(Time_T dt)
{
    // (p(t + dt) - p(t)) / dt = v(t)
    // so: p(t + dt) = p(t) + v(t) * dt
    this->translate(m_velocity * dt);
}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
CANT_INLINE void
  KineticObject<Len_T, Mass_T, Time_T, dim>::clearForceBuffer()
{
    m_buffer.deltaForce = DeltaForce();
}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
void
  KineticObject<Len_T, Mass_T, Time_T, dim>::setMass(Mass_T mass)
{
    CANTINA_ASSERT(!maths::approx<Mass_T>::equal(static_cast<Mass_T>(0), mass), "Noooo");
    m_inverseMass = static_cast<Mass_T>(1) / mass;
    // Now, let's pretend this did not happen and that the
    // constant mass hypothesis still stands, so that we can use:
    // dP = d(mass * velocity) = mass * dvelocity
}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
CANT_INLINE typename KineticObject<Len_T, Mass_T, Time_T, dim>::Velocity const &
  KineticObject<Len_T, Mass_T, Time_T, dim>::getVelocity() const
{
    return m_velocity;
}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
CANT_INLINE void
  KineticObject<Len_T, Mass_T, Time_T, dim>::setVelocity(KineticObject::Velocity velocity)
{
    m_velocity = std::move(velocity);
}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
Mass_T
  KineticObject<Len_T, Mass_T, Time_T, dim>::getInverseMass() const
{
    return m_inverseMass;
}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
CANT_INLINE typename KineticObject<Len_T, Mass_T, Time_T, dim>::Acceleration const &
  KineticObject<Len_T, Mass_T, Time_T, dim>::getAcceleration() const
{
    return m_acceleration;
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_KINETICOBJECT_INL
