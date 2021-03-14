
#ifndef CANTINA_PHYSICS_CUSTOMFORCEFIELD_INL
#define CANTINA_PHYSICS_CUSTOMFORCEFIELD_INL

#pragma once

#include <algorithm>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
CustomForceField<dim, T>::CustomForceField(DeltaForceFunctor func)
  : m_func(std::move(func))
{
}

template <size_u dim, typename T>
typename CustomForceField<dim, T>::Vector
CustomForceField<dim, T>::getDeltaForce(ShPtr<Object> const & object) const
{
    return m_func(object);
}
template <size_u dim, typename T>
void
  CustomForceField<dim, T>::setDeltaForceFunctor(DeltaForceFunctor func)

{
    m_func = std::move(func);
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_CUSTOMFORCEFIELD_INL