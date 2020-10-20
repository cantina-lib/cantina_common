#ifndef CANTINA_PHYSICALCOLLISION_INL
#define CANTINA_PHYSICALCOLLISION_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

    template<typename Len_T, typename Mass_T, size_u dim>
    PhysicalCollision<Len_T, Mass_T, dim>::
    PhysicalCollision(CollisionPair pair)
        : m_pair(std::move(pair)),
        m_phase(eEnter)
    {
        sortColliders();
        computeContact();
    }

    template<typename Len_T, typename Mass_T, size_u dim>
    CANT_INLINE
    void
    PhysicalCollision<Len_T, Mass_T, dim>::
    computeCollision()
    {
        switch (getPhase())
        {
            case eEnter: setCollidersVelocities(); break;
            case eStay:  setCollidersSupport(); break;
            case eLeave: break;
        }
    }

    template<typename Len_T, typename Mass_T, size_u dim>
    CANT_INLINE
    ShPtr <typename PhysicalCollision<Len_T, Mass_T, dim>::Collider> &
    PhysicalCollision<Len_T, Mass_T, dim>::
    getColliderMax()
    {
        return m_pair.first;
    }

    template<typename Len_T, typename Mass_T, size_u dim>
    CANT_INLINE
    ShPtr <typename PhysicalCollision<Len_T, Mass_T, dim>::Collider> &
    PhysicalCollision<Len_T, Mass_T, dim>::
    getColliderMin()
    {
        return m_pair.second;
    }

    template<typename Len_T, typename Mass_T, size_u dim>
    CANT_INLINE
    void
    PhysicalCollision<Len_T, Mass_T, dim>::
    computeContact()
    {
        // rap, rbp
        m_contact.rap = getColliderMin()->getVectorToClosestRim(getColliderMax()->getCentre());

        // n
        if (maths::approx<Len_T>::equal(static_cast<Len_T>(0), m_contact.rap.getNorm()))
        {
            m_contact.n = Vector();
            m_contact.n.template set<0>(static_cast<Len_T>(1));
        }
        else
        {
            // sphere, so yeah.
            m_contact.n = - m_contact.rap.getNormalised();
        }

        // no angular velocity for now.

        // impact point velocities
        // same as centre of mass because there are no rotations.
        m_contact.vap = getColliderMax()->getVelocity();
        m_contact.vbp = getColliderMin()->getVelocity();

        // elasticity (restitution)
        m_contact.e = c_restitution;

        // impulse j
        Velocity const vab = m_contact.vap - m_contact.vbp;
        Len_T const nom = - (static_cast<Len_T>(1) + m_contact.e) * vab.dot(m_contact.n);
        Len_T const den = getColliderMax()->getInverseMass() + getColliderMin()->getInverseMass();

        m_contact.impulse = nom / den;
    }

    template<typename Len_T, typename Mass_T, size_u dim>
    void
    PhysicalCollision<Len_T, Mass_T, dim>::
    sortColliders()
    {
        bool const firstIsStatic = m_pair.first->isStatic();
        bool const secondIsStatic = m_pair.second->isStatic();

        CANTINA_ASSERT(!(firstIsStatic && secondIsStatic), "Not supposed to happen!");

        bool shouldSwap;
        if (!(firstIsStatic || secondIsStatic))
        {
            Len_T const velNorm1 = m_pair.first->getVelocity().getNorm();
            Len_T const velNorm2 = m_pair.second->getVelocity().getNorm();

            shouldSwap = velNorm2 >= velNorm1;
        }
        else
        {
            shouldSwap = firstIsStatic;
        }
        if (shouldSwap)
        {
            std::swap(m_pair.first, m_pair.second);
        }
    }

    template<typename Len_T, typename Mass_T, size_u dim>
    void
    PhysicalCollision<Len_T, Mass_T, dim>::
    setCollidersVelocities()
    {
        getColliderMin()->setVelocity
        (
            getColliderMin()->getVelocity()
            - m_contact.n * (m_contact.impulse * getColliderMin()->getInverseMass())
        );
        getColliderMax()->setVelocity
        (
            getColliderMax()->getVelocity()
            + m_contact.n * (m_contact.impulse * getColliderMax()->getInverseMass())
        );
    }

    template<typename Len_T, typename Mass_T, size_u dim>
    void
    PhysicalCollision<Len_T, Mass_T, dim>::
    setCollidersSupport()
    {
        CANT_MAYBEUNUSED Acceleration apna = m_contact.n.dot(getColliderMax()->getAcceleration());
        CANT_MAYBEUNUSED Acceleration apnb = - m_contact.n.dot(getColliderMin()->getAcceleration());


    }


    template<typename Len_T, typename Mass_T, size_u dim>
    CANT_INLINE
    void
    PhysicalCollision<Len_T, Mass_T, dim>::
    setPhase(PhysicalCollision::ContactPhase phase)
    {
        m_phase = phase;
    }

    template<typename Len_T, typename Mass_T, size_u dim>
    CANT_INLINE
    typename PhysicalCollision<Len_T, Mass_T, dim>::ContactPhase
    PhysicalCollision<Len_T, Mass_T, dim>::
    getPhase() const
    {
        return m_phase;
    }

    template<typename Len_T, typename Mass_T, size_u dim>
    CANT_INLINE
    bool
    PhysicalCollision<Len_T, Mass_T, dim>::
    haveSameColliders(PhysicalCollision const& other) const
    {
        return other.m_pair.first == this->m_pair.first
            && other.m_pair.second == this->m_pair.second;
    }


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_PHYSICALCOLLISION_INL