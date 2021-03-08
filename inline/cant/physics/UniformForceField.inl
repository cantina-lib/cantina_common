
#ifndef CANTINA_PHYSICS_UNIFORMFORCEFIELD_INL
#define CANTINA_PHYSICS_UNIFORMFORCEFIELD_INL

#pragma once

#include <algorithm>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template<size_u dim, typename T>
UniformForceField<dim, T>::UniformForceField(
        ObjectStream & objects, Vector vec)
        : ForceField(objects), m_vec(std::move(vec))
{
}

template<size_u dim, typename T>
UniformForceField<dim, T>::UniformForceField(Vector vec)
  : m_vec(std::move(vec))
{
}

template <size_u dim, typename T>
typename UniformForceField<dim, T>::Vector
UniformForceField<dim, T>::getDeltaForce(CANT_MAYBEUNUSED const ShPtr<Object> & object) const
{
    return m_vec;
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_UNIFORMFORCEFIELD_INL