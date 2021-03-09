
#ifndef CANTINA_PHYSICS_LEAPFROGUPDATER_INL
#define CANTINA_PHYSICS_LEAPFROGUPDATER_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template<size_u dim, typename T>
void LeapfrogUpdater<dim, T>::stepDeltaInternal(ShPtr<Object> &object, T dt) const
{
    // first update velocity from acceleration
    this->template updateVelocity(object, dt);
    // then update the position.
    this->template updatePosition(object, dt);
}

CANTINA_PHYSICS_NAMESPACE_END

#include <cant/common/undef_macro.hpp>
#endif  // CANTINA_PHYSICS_KINETICOBJECT_INL
