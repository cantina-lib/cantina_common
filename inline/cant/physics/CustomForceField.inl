
#ifndef CANTINA_PHYSICS_CUSTOMFORCEFIELD_INL
#define CANTINA_PHYSICS_CUSTOMFORCEFIELD_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    typename CustomForceField<Len_T, Mass_T, Time_T, dim>::ForceField::DeltaForce
    CustomForceField<Len_T, Mass_T, Time_T, dim>::
    getDeltaForce(UPtr<typename ForceField::State> const& previous) const
    {
        return m_func(previous, this->m_dt);
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CustomForceField<Len_T, Mass_T, Time_T, dim>::
    CustomForceField(CustomForceField::DeltaForceFunctor func)
    : m_func(std::move(func))
    { }

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_PHYSICS_CUSTOMFORCEFIELD_INL
