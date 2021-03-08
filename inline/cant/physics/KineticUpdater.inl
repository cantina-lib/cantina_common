
#ifndef CANTINA_PHYSICS_KINETICUPDATER_INL
#define CANTINA_PHYSICS_KINETICUPDATER_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template<size_u dim, typename T>
void KineticUpdater<dim, T>::stepDelta(ShPtr<Object> &object, T dt ) const
{
    stepDeltaInternal(object, dt);
    // Clear all
    object->clearForceBuffer();
}

CANTINA_PHYSICS_NAMESPACE_END

#include <cant/common/undef_macro.hpp>
#endif  // CANTINA_PHYSICS_KINETICOBJECT_INL
