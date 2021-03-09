
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
        : m_objects()
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
    Stream<Vector> deltaForces;
    deltaForces.reserve(m_objects->size());
    // Compute and apply delta force to object.
    for (size_u i = 0; i < m_objects->size(); ++i)
    {
        auto const & obj = m_objects->at(i);
        if (!obj->hasFlags(FObjectBehaviour::fNoFieldObject | FObjectBehaviour::fStaticObject))
        {
            deltaForces.push_back(getDeltaForce(obj));
        }
    }
    for (size_u i = 0; i < m_objects->size(); ++i)
    {
        auto & obj = m_objects->at(i);
        if (!obj->hasFlags(FObjectBehaviour::fNoFieldObject | FObjectBehaviour::fStaticObject))
        {
            obj->addDeltaForce(deltaForces.at(i));
        }
    }
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICALFORCE_INL