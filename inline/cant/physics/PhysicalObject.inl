
#ifndef CANTINA_PHYSICS_PHYSICALOBJECT_INL
#define CANTINA_PHYSICS_PHYSICALOBJECT_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <typename Len_T, size_u dim>
PhysicalObject<Len_T, dim>::PhysicalObject(Position position) : m_position(std::move(position))
{}

template <typename Len_T, size_u dim>
PhysicalObject<Len_T, dim>::PhysicalObject() : m_position()
{}

template <typename Len_T, size_u dim>
CANT_INLINE void
  PhysicalObject<Len_T, dim>::setPosition(Position pos)
{
    m_position = std::move(pos);
}

template <typename Len_T, size_u dim>
CANT_INLINE typename PhysicalObject<Len_T, dim>::Position const &
  PhysicalObject<Len_T, dim>::getPosition() const
{
    return m_position;
}

template <typename Len_T, size_u dim>
void
  PhysicalObject<Len_T, dim>::translate(PhysicalObject::Vector const & vec)
{
    m_position += vec;
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICALOBJECT_INL
