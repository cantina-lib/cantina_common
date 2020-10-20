
#ifndef CANTINA_PHYSICS_KINETICSTATE_INL
#define CANTINA_PHYSICS_KINETICSTATE_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    KineticState<Len_T, Mass_T, Time_T, dim>::
    KineticState(Mass_T mass, Position position)
	   : PhysicalState<Len_T, dim>(std::move(position)),
	   m_inverseMass(),
	   m_velocity(),
	   m_acceleration(),
	   m_buffer()
    {
        setMass(mass);
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    KineticState<Len_T, Mass_T, Time_T, dim>::
    KineticState(Mass_T mass)
        : KineticState(mass, Position())
    {

    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    void
    KineticState<Len_T, Mass_T, Time_T, dim>::
    stepDelta(Time_T dt)
    {
    	/*
    	 * the following lines are of the utmost importance, pay heed.
    	 * remember that what change in position an object has
    	 * should undergo at t + dt
    	 * is in fact its velocity at t !!!
    	 * see below:
    	 * p(t + dt) = p(t) + dv * dt
    	 * As such the position should be updated BEFORE the velocity,
    	 * and, for the same reason, the velocity BEFORE the acceleration.
    	 * BUT, in our case we care about immediate change,
    	 * so we reverse the order, so that p(t + dt) can be accessed without lag.
    	 */
        updateAccelerationFromAccumulatedForce();
        updatePositionFromVelocity(dt);
        updateVelocityFromAcceleration(dt);
    	clearAccumulatedDeltaForce();
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    void
    KineticState<Len_T, Mass_T, Time_T, dim>::
    addDeltaForce(DeltaForce const& dF)
    {
    	m_buffer.deltaForce += dF;
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    void
    KineticState<Len_T, Mass_T, Time_T, dim>::
    updateAccelerationFromAccumulatedForce()
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

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    void
    KineticState<Len_T, Mass_T, Time_T, dim>::
    updateVelocityFromAcceleration(Time_T dt)
    {
    	//         v(t + dt) = v(t) + dv(t)
    	// with:     dv(t) = a(t) * dt
    	// hence:  v(t + dt) = v(t) + a(t) * dt
    	m_velocity += m_acceleration * dt;
    }


    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    void
    KineticState<Len_T, Mass_T, Time_T, dim>::
    updatePositionFromVelocity(Time_T dt)
    {
    	// (p(t + dt) - p(t)) / dt = v(t)
    	// so: p(t + dt) = p(t) + v(t) * dt
    	this->translate(m_velocity * dt);
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    void
    KineticState<Len_T, Mass_T, Time_T, dim>::
    clearAccumulatedDeltaForce()
    {
        m_buffer.deltaForce = DeltaForce();
    }


    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    void
    KineticState<Len_T, Mass_T, Time_T, dim>::
    setMass(Mass_T mass)
    {
        CANTINA_ASSERT(!maths::approx<Mass_T>::equal(static_cast<Mass_T>(0), mass), "Noooo");
        m_inverseMass = static_cast<Mass_T>(1) / mass;
        // Now, let's pretend this did not happen and that the
        // constant mass hypothesis still stands, so that we can use:
        // dP = d(mass * velocity) = mass * dvelocity
    }


    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    typename KineticState<Len_T, Mass_T, Time_T, dim>::Velocity const&
    KineticState<Len_T, Mass_T, Time_T, dim>::
    getVelocity() const
    {
        return m_velocity;
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    void
    KineticState<Len_T, Mass_T, Time_T, dim>::
    setVelocity(KineticState::Velocity velocity)
    {
        m_velocity = std::move(velocity);
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    Mass_T
    KineticState<Len_T, Mass_T, Time_T, dim>::
    getInverseMass() const
    {
        return m_inverseMass;
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    typename KineticState<Len_T, Mass_T, Time_T, dim>::Acceleration const&
    KineticState<Len_T, Mass_T, Time_T, dim>::
    getAcceleration() const
    {
        return m_acceleration;
    }

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_PHYSICS_KINETICSTATE_INL
