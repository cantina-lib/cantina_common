
#ifndef CANTINA_PHYSICS_PHYSICALFORCEFIELD_INL
#define CANTINA_PHYSICS_PHYSICALFORCEFIELD_INL

#pragma once

#include <algorithm>

#include <cant/physics/Flags.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template<size_u dim, typename T>
PhysicalForceField<dim, T>::PhysicalForceField(
        ObjectStream const & objects)
        : m_objects(), m_isEnabled(true)
{
    setObjects(objects);
}

template<size_u dim, typename T>
PhysicalForceField<dim, T>::PhysicalForceField()
{
    setObjects(std::make_shared<Stream<ShPtr<Object>>>());
}

template <size_u dim, typename T>
void
PhysicalForceField<dim, T>::setObjects(ObjectStream const & objects)
{
    // m_objects should never be nullptr
    CANTINA_ASSERT(objects.get() != nullptr, "Stream of objects is not allocated!");
    m_objects = objects;
}

template <size_u dim, typename T>
void
PhysicalForceField<dim, T>::apply() const
{
    if (!isEnabled())
    {
        return;
    }
    Stream<Vector> deltaForces;
    deltaForces.reserve(m_objects->size());
    // Compute and apply delta force to object.
    // todo: better object handling.
    for (size_u i = 0; i < m_objects->size(); ++i)
    {
        auto const & obj = m_objects->at(i);
        if (!(obj->hasFlag(FObjectBehaviour::fNoFieldObject) || obj->hasFlag(FObjectBehaviour::fStaticObject)))
        {
            deltaForces.push_back(getDeltaForce(obj));
        }
    }
    // use a second counter to filter non-field objects and match deltaForces.
    size_u j = 0;
    for (size_u i = 0; i < m_objects->size(); ++i)
    {
        auto & obj = m_objects->at(i);
        if (!(obj->hasFlag(FObjectBehaviour::fNoFieldObject) || obj->hasFlag(FObjectBehaviour::fStaticObject)))
        {
            obj->addDeltaForce(deltaForces.at(j));
            ++j;
        }
    }
}
template <size_u dim, typename T>
void
  PhysicalForceField<dim, T>::setEnabled(bool enabled)
{
    m_isEnabled = enabled;
}

template <size_u dim, typename T>
bool
  PhysicalForceField<dim, T>::isEnabled() const
{
    return m_isEnabled;
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICALFORCE_INL