
#ifndef CANTINA_PHYSICS_WEAKREFPHYSICALFORCE_INL
#define CANTINA_PHYSICS_WEAKREFPHYSICALFORCE_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
void
WeakRefPhysicalForce<dim, T>::apply() const
{
    const size_u numberObjects = getNumberObjects();
    WPtr<Object> const * objectRefs = getObjects();

    // create stream of objects to pass to derived class
    Stream<ShPtr<Object>> objects;
    objects.reserve(numberObjects);
    for (size_u i = 0; i < numberObjects; ++i)
    {
        if (auto object = objectRefs[i].lock())
        {
            objects.push_back(object);
        }
    }

    // Actually, all objects should be valid at this time,
    // because lost objects should be removed by this point,
    // so we should assert.
    // Actually, no.
    // CANTINA_ASSERT(objects.size() == numberObjects, "Objects should not be invalid at this point.");

    Stream<Vector> deltaForces(objects.size());

    // this method will fill all delta forces of the objects
    getDeltaForce(objects, deltaForces);

    // now apply the delta force to each object.
    for (size_u i = 0; i < objects.size(); ++i)
    {
        objects.at(i)->addDeltaForce(deltaForces.at(i));
    }
}

template<size_u dim, typename T>
void WeakRefPhysicalForce<dim, T>::cleanUp()
{

}

template <size_u dim, typename T>
CANT_INLINE
  WeakRefPhysicalForce<dim, T>::WeakRefPhysicalForce()
    : Force()
{}


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICALFORCE_INL