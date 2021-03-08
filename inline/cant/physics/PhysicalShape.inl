
#ifndef CANTINA_PHYSICS_PHYSICALSHAPE_INL
#define CANTINA_PHYSICS_PHYSICALSHAPE_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
CANT_INLINE bool
  PhysicalShape<dim, T>::isInObject(Position const & pos) const
{
    return getRadius() <= pos.getDistance(m_centreObject);
}

template <size_u dim, typename T>
CANT_INLINE typename PhysicalShape<dim, T>::Vector
  PhysicalShape<dim, T>::getVectorToCentreObject(PhysicalShape::Position const & pos) const
{
    return m_centreObject - pos;
}

template <size_u dim, typename T>
CANT_INLINE T
  PhysicalShape<dim, T>::getRadius() const
{
    return m_radius;
}

template <size_u dim, typename T>
CANT_INLINE typename PhysicalShape<dim, T>::Position const &
  PhysicalShape<dim, T>::getCentreObject() const
{
    return m_centreObject;
}

template <size_u dim, typename T>
bool
  PhysicalShape<dim, T>::intersectsObject(UPtr<PhysicalShape> const & other,
                                              Position const &            centreThis,
                                              Position const &            centreOther) const
{
    // get vec of centre to centre
    return centreThis.getDistance(centreOther) <= this->getRadius() + other->getRadius();
}

template <size_u dim, typename T>
PhysicalShape<dim, T>::PhysicalShape(Position centreObject, T radius)
    : m_centreObject(std::move(centreObject)), m_radius(radius)
{}

template <size_u dim, typename T>
PhysicalShape<dim, T>::~PhysicalShape() = default;

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICALSHAPE_INL