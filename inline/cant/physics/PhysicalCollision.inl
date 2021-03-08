#ifndef CANTINA_PHYSICALCOLLISION_INL
#define CANTINA_PHYSICALCOLLISION_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
PhysicalCollision<dim, T>::PhysicalCollision(CollisionPair pair) : m_pair(std::move(pair)), m_phase(eEnter)
{
    sortColliders();
    computeContact();
}

template <size_u dim, typename T>
CANT_INLINE void
  PhysicalCollision<dim, T>::computeCollision()
{
    switch (getPhase())
    {
    case eEnter: setCollidersVelocities(); break;
    case eStay: setCollidersSupport(); break;
    case eLeave: break;
    }
}

template <size_u dim, typename T>
CANT_INLINE ShPtr<typename PhysicalCollision<dim, T>::Collider> &
            PhysicalCollision<dim, T>::getColliderMax()
{
    return m_pair.first;
}

template <size_u dim, typename T>
CANT_INLINE ShPtr<typename PhysicalCollision<dim, T>::Collider> &
            PhysicalCollision<dim, T>::getColliderMin()
{
    return m_pair.second;
}

template <size_u dim, typename T>
CANT_INLINE void
  PhysicalCollision<dim, T>::computeContact()
{
    // rap, rbp
    m_contact.rap = getColliderMin()->getVectorToClosestRim(getColliderMax()->getCentre());

    // n
    if (maths::approx<T>::equal(static_cast<T>(0), m_contact.rap.getNorm()))
    {
        m_contact.n = Vector();
        m_contact.n.template set<0>(static_cast<T>(1));
    }
    else
    {
        // sphere, so yeah.
        m_contact.n = -m_contact.rap.getNormalised();
    }

    // no angular velocity for now.

    // impact point velocities
    // same as centre of mass because there are no rotations.
    m_contact.vap = getColliderMax()->getVelocity();
    m_contact.vbp = getColliderMin()->getVelocity();

    // elasticity (restitution)
    m_contact.e = c_restitution;

    // impulse j
    Vector const vab = m_contact.vap - m_contact.vbp;
    T const    nom = -(static_cast<T>(1) + m_contact.e) * vab.dot(m_contact.n);
    T const    den = getColliderMax()->getInverseMass() + getColliderMin()->getInverseMass();

    m_contact.impulse = nom / den;
}

template <size_u dim, typename T>
void
  PhysicalCollision<dim, T>::sortColliders()
{
    bool const firstIsStatic  = m_pair.first->isStatic();
    bool const secondIsStatic = m_pair.second->isStatic();

    CANTINA_ASSERT(!(firstIsStatic && secondIsStatic), "Not supposed to happen!");

    bool shouldSwap;
    if (!(firstIsStatic || secondIsStatic))
    {
        T const velNorm1 = m_pair.first->getVelocity().getNorm();
        T const velNorm2 = m_pair.second->getVelocity().getNorm();

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

template <size_u dim, typename T>
void
  PhysicalCollision<dim, T>::setCollidersVelocities()
{
    getColliderMin()->setVelocity(getColliderMin()->getVelocity()
                                  - m_contact.n * (m_contact.impulse * getColliderMin()->getInverseMass()));
    getColliderMax()->setVelocity(getColliderMax()->getVelocity()
                                  + m_contact.n * (m_contact.impulse * getColliderMax()->getInverseMass()));
}

template <size_u dim, typename T>
void
  PhysicalCollision<dim, T>::setCollidersSupport()
{
    CANT_MAYBEUNUSED Vector apna = m_contact.n.dot(getColliderMax()->getAcceleration());
    CANT_MAYBEUNUSED Vector apnb = -m_contact.n.dot(getColliderMin()->getAcceleration());
}

template <size_u dim, typename T>
CANT_INLINE void
  PhysicalCollision<dim, T>::setPhase(PhysicalCollision::ContactPhase phase)
{
    m_phase = phase;
}

template <size_u dim, typename T>
CANT_INLINE typename PhysicalCollision<dim, T>::ContactPhase
  PhysicalCollision<dim, T>::getPhase() const
{
    return m_phase;
}

template <size_u dim, typename T>
CANT_INLINE bool
  PhysicalCollision<dim, T>::haveSameColliders(PhysicalCollision const & other) const
{
    return other.m_pair.first == this->m_pair.first && other.m_pair.second == this->m_pair.second;
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICALCOLLISION_INL