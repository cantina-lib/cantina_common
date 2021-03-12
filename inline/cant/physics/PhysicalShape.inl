
#ifndef CANTINA_PHYSICS_PHYSICALSHAPE_INL
#define CANTINA_PHYSICS_PHYSICALSHAPE_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
PhysicalShape<dim, T>::PhysicalShape(DistanceFunctor func, T radius)
    : m_func(std::move(func)), m_radius(radius)
{

}

template <size_u dim, typename T>
PhysicalShape<dim, T>::~PhysicalShape() = default;

template <size_u dim, typename T>
CANT_INLINE T
  PhysicalShape<dim, T>::getRadius() const
{
    return m_radius;
}
template <size_u dim, typename T>
Optional<typename PhysicalShape<dim, T>::Position>
  PhysicalShape<dim, T>::getIntersection(CANT_MAYBEUNUSED const UPtr<PhysicalShape> &     other,
                                         CANT_MAYBEUNUSED const Position & centreThis,
                                         CANT_MAYBEUNUSED const Position & centreOther) const
{
    // todo!
    return Optional<Position>();
}


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICALSHAPE_INL