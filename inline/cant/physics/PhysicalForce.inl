
#ifndef CANTINA_PHYSICS_PHYSICALFORCE_INL
#define CANTINA_PHYSICS_PHYSICALFORCE_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
CANT_INLINE bool
  PhysicalForce<Len_T, Mass_T, Time_T, dim>::hasExpired() const
{
    return m_hasEnded;
}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
CANT_INLINE void
  PhysicalForce<Len_T, Mass_T, Time_T, dim>::signalExpired() const
{
    m_hasEnded = true;
}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
CANT_INLINE
  PhysicalForce<Len_T, Mass_T, Time_T, dim>::PhysicalForce()
    : m_hasEnded(false)
{}


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICALFORCE_INL