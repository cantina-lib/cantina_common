
#ifndef CANTINA_PHYSICS_PHYSICALFORCE_INL
#define CANTINA_PHYSICS_PHYSICALFORCE_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
CANT_INLINE bool
  PhysicalForce<dim, T>::hasExpired() const
{
    return m_hasEnded;
}

template <size_u dim, typename T>
CANT_INLINE void
  PhysicalForce<dim, T>::signalExpired() const
{
    m_hasEnded = true;
}

template <size_u dim, typename T>
CANT_INLINE
  PhysicalForce<dim, T>::PhysicalForce()
    : m_hasEnded(false)
{}


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICALFORCE_INL