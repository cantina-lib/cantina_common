
#ifndef CANTINA_PHYSICS_KINETICOBJECT_INL
#define CANTINA_PHYSICS_KINETICOBJECT_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    void
    KineticObject<Len_T, Mass_T, Time_T, dim>::
    stepDelta(Time_T dt)
    {
    	// accumulate deltaForce in state.
    	for (auto it = m_appliedForce.begin(); it != m_appliedForce.end(); ++it)
    	{
    	    UPtr<AppliedForce>& appliedForce = *it;
    	    if (appliedForce->hasEnded())
            {
    	       m_appliedForce.erase(it);
            }
    	    else
            {
    	        appliedForce->stepDelta(dt);
                this->m_state->addDeltaForce(appliedForce->getDeltaForce(this->m_state));
            }
    	}

    	// apply the changes and update the state.
        this->m_state->stepDelta(dt);
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    void
    KineticObject<Len_T, Mass_T, Time_T, dim>::
    addAppliedForce(UPtr <AppliedForce> force)
    {
        m_appliedForce.push_back(std::move(force));
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    void
    KineticObject<Len_T, Mass_T, Time_T, dim>::
    clearAppliedForces()
    {
        m_appliedForce.clear();
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    void
    KineticObject<Len_T, Mass_T, Time_T, dim>::
    setMass(Mass_T mass)
    {
    	this->m_state->setMass(mass);
    }

    template<typename Dim_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    KineticObject<Dim_T, Mass_T, Time_T, dim>::
    KineticObject(UPtr<State> state)
        : PhysicalObjectTrait<State, Dim_T, dim>(std::move(state))
    { }

    template<typename Dim_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    void
    KineticObject<Dim_T, Mass_T, Time_T, dim>::
    addDeltaForceField(ShPtr<ForceField> const& forceField)
    {
        this->m_state->addDeltaForce(forceField->getDeltaForce(this->m_state));
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    typename KineticObject<Len_T, Mass_T, Time_T, dim>::Velocity const&
    KineticObject<Len_T, Mass_T, Time_T, dim>::
    getVelocity() const
    {
        return this->m_state->getVelocity();
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    Mass_T
    KineticObject<Len_T, Mass_T, Time_T, dim>::
    getInverseMass() const
    {
        return this->m_state->getInverseMass();
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    void
    KineticObject<Len_T, Mass_T, Time_T, dim>::
    setVelocity(KineticObject::Velocity velocity)
    {
        this->m_state->setVelocity(std::move(velocity));
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    typename KineticObject<Len_T, Mass_T, Time_T, dim>::Acceleration const&
    KineticObject<Len_T, Mass_T, Time_T, dim>::
    getAcceleration() const
    {
        return this->m_state->getAcceleration();
    }


CANTINA_PHYSICS_NAMESPACE_END

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_PHYSICS_KINETICOBJECT_INL
