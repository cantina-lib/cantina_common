
#ifndef CANTINA_PHYSICS_PHYSICALSTATE_INL
#define CANTINA_PHYSICS_PHYSICALSTATE_INL

#pragma once

#include <cant/common/macro.hpp>
#include <cant/physics/PhysicalState.hpp>

CANTINA_PHYSICS_NAMESPACE_BEGIN

template <typename Len_T, size_u dim>
PhysicalState<Len_T, dim>::PhysicalState(Position position) : m_position(std::move(position))
{}

template <typename Len_T, size_u dim>
PhysicalState<Len_T, dim>::PhysicalState() : m_position()
{}

template <typename Len_T, size_u dim>
CANT_INLINE void
  PhysicalState<Len_T, dim>::setPosition(Position pos)
{
    m_position = std::move(pos);
}

template <typename Len_T, size_u dim>
CANT_INLINE typename PhysicalState<Len_T, dim>::Position const &
  PhysicalState<Len_T, dim>::getPosition() const
{
    return m_position;
}

template <typename Len_T, size_u dim>
void
  PhysicalState<Len_T, dim>::translate(PhysicalState::Vector const & vec)
{
    m_position += vec;
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICALSTATE_INL
