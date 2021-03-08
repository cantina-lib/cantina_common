
#ifndef CANTINA_PHYSICS_UNIFORMFORCEFIELD_INL
#define CANTINA_PHYSICS_UNIFORMFORCEFIELD_INL

#pragma once

#include <algorithm>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
UniformForceField<Len_T, Mass_T, Time_T, dim>::UniformForceField(
        ObjectStream & objects, DeltaForce vec)
        : ForceField(objects), m_vec(std::move(vec))
{
}

template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
UniformForceField<Len_T, Mass_T, Time_T, dim>::UniformForceField(DeltaForce vec)
  : m_vec(std::move(vec))
{
}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
typename UniformForceField<Len_T, Mass_T, Time_T, dim>::DeltaForce
UniformForceField<Len_T, Mass_T, Time_T, dim>::getDeltaForce(ShPtr<Object> const & object) const
{
    return m_vec;
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_UNIFORMFORCEFIELD_INL