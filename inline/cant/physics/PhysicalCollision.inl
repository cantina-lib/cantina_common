#ifndef CANTINA_PHYSICALCOLLISION_INL
#define CANTINA_PHYSICALCOLLISION_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
PhysicalCollision<dim, T>::PhysicalCollision(CollisionPair pair, Intersection intersection)
    : m_pair(std::move(pair)), m_intersection(std::move(intersection)),
      m_phase(eEnter)
{
    sortColliders();
    computeContact();
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
    // rap ->
    m_contact.rap = m_intersection.centre - getColliderMax()->getCentreWorld();
    m_contact.n = - m_intersection.normal;

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
    if (!firstIsStatic && !secondIsStatic)
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
        // also swapping direction!
        m_intersection.normal = - m_intersection.normal;
        std::swap(m_pair.first, m_pair.second);
    }
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

template <size_u dim, typename T>
CANT_INLINE typename PhysicalCollision<dim, T>::Contact const &
PhysicalCollision<dim, T>::getContact() const
{
    return m_contact;
}

template <size_u dim, typename T>
CANT_INLINE typename PhysicalCollision<dim, T>::Intersection const &
PhysicalCollision<dim, T>::getIntersection() const
{
    return m_intersection;
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICALCOLLISION_INL