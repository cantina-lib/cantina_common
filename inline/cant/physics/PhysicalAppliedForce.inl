
#ifndef CANTINA_PHYSICS_PHYSICALAPPLIEDFORCE_INL
#define CANTINA_PHYSICS_PHYSICALAPPLIEDFORCE_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
PhysicalAppliedForce<Len_T, Mass_T, Time_T, dim>::PhysicalAppliedForce() = default;

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICALAPPLIEDFORCE_INL