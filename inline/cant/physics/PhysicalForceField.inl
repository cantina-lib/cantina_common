
#ifndef CANTINA_PHYSICS_PHYSICALFORCEFIELD_INL
#define CANTINA_PHYSICS_PHYSICALFORCEFIELD_INL

#pragma once

#include <algorithm>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
PhysicalForceField<Len_T, Mass_T, Time_T, dim>::PhysicalForceField(
        ObjectStream const & objects)
        : m_objects()
{
    setObjects(objects);
}

template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
PhysicalForceField<Len_T, Mass_T, Time_T, dim>::PhysicalForceField()
{
    setObjects(std::make_shared<Stream<ShPtr<Object>>>());
}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
void
PhysicalForceField<Len_T, Mass_T, Time_T, dim>::setObjects(ObjectStream const & objects)
{
    // m_objects should never be nullptr
    CANTINA_ASSERT(objects.get() != nullptr, "Stream of objects is not allocated!");
    m_objects = objects;
}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
void
PhysicalForceField<Len_T, Mass_T, Time_T, dim>::apply() const
{
    Stream<DeltaForce> deltaForces;
    deltaForces.reserve(m_objects->size());
    // Compute and apply delta force to object.
    for (size_u i = 0; i < m_objects->size(); ++i)
    {
        auto const & obj = m_objects->at(i);
        deltaForces.push_back(getDeltaForce(obj));
    }
    for (size_u i = 0; i < m_objects->size(); ++i)
    {
        auto & obj = m_objects->at(i);
        obj->addDeltaForce(deltaForces.at(i));
    }
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICALFORCE_INL