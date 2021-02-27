
#ifndef CANTINA_PHYSICS_KINETICUPDATER_INL
#define CANTINA_PHYSICS_KINETICUPDATER_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
void KineticUpdater<Len_T, Mass_T, Time_T, dim>::stepDelta(ShPtr<Object> &object, Time_T dt ) const
{
    stepDeltaInternal(object, dt);
    // Clear all
    object->clearForceBuffer();
}

CANTINA_PHYSICS_NAMESPACE_END

#include <cant/common/undef_macro.hpp>
#endif  // CANTINA_PHYSICS_KINETICOBJECT_INL
