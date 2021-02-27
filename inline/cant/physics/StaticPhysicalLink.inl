
#ifndef CANTINA_PHYSICS_PHYSICALLINK_INL
#define CANTINA_PHYSICS_PHYSICALLINK_INL

#pragma once

#include <algorithm>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template<typename Len_T, typename Mass_T, typename Time_T, size_u dim, size_u numberObjects>
StaticPhysicalLink<Len_T, Mass_T, Time_T, dim, numberObjects>::StaticPhysicalLink(
        StaticPhysicalLink::ObjectArray objects)
        : m_objectRefs()
{
    for (size_u i = 0; i < objects.size(); ++i)
    {
        m_objectRefs.at(i) = objects.at(i);
    }
}

template<typename Len_T, typename Mass_T, typename Time_T, size_u dim, size_u numberObjects>
void StaticPhysicalLink<Len_T, Mass_T, Time_T, dim, numberObjects>::getDeltaForce(
        Stream<ShPtr<Object>> const & objects, Stream<DeltaForce> & deltaForces) const
{
    CANTINA_ASSERT(objects.size() == deltaForces.size(), "noooo");

    // some checks before leaving the work to the derived class.
    if (objects.size() != numberObjects)
    {
        // this one should be removed!
        return;
    }
    getDeltaForceInternal(objects, deltaForces);
}

template <typename Len_T, typename  Mass_T, typename Time_T, size_u dim, size_u numberObjects>
size_u
StaticPhysicalLink<Len_T, Mass_T, Time_T, dim, numberObjects>::getNumberObjects() const
{
    return numberObjects;
}

template <typename Len_T, typename  Mass_T, typename Time_T, size_u dim, size_u numberObjects>
WPtr<typename StaticPhysicalLink<Len_T, Mass_T, Time_T, dim, numberObjects>::Object> const *
StaticPhysicalLink<Len_T, Mass_T, Time_T, dim, numberObjects>::getObjects() const
{
    return m_objectRefs.data();
}

template <typename Len_T, typename  Mass_T, typename Time_T, size_u dim, size_u numberObjects>
void
StaticPhysicalLink<Len_T, Mass_T, Time_T, dim, numberObjects>::cleanUp()
{
    // can't really do any clean-up here.
    // Static links should not be allow to function if any of their objects is lost.
    // Also, checking for expiration of references here is not enough to ensure that
    // they will not have expired a bit later (not thread-safe, not atomic).
    // but it's better than nothing.
    if (std::any_of(m_objectRefs.begin(), m_objectRefs.end(), [](auto & ref) { return ref.expired(); }))
    {
        this->template signalExpired();
    }
}



CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICALFORCE_INL