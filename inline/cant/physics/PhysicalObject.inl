
#ifndef CANTINA_PHYSICS_PHYSICALOBJECT_INL
#define CANTINA_PHYSICS_PHYSICALOBJECT_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
PhysicalObject<dim, T>::PhysicalObject(Position position)
    : m_position(std::move(position)), m_flags(c_defaultObjectFlags)
{}

template <size_u dim, typename T>
CANT_INLINE void
  PhysicalObject<dim, T>::setPosition(Position pos)
{
    m_position = std::move(pos);
}

template <size_u dim, typename T>
CANT_INLINE typename PhysicalObject<dim, T>::Position const &
  PhysicalObject<dim, T>::getPosition() const
{
    return m_position;
}

template <size_u dim, typename T>
void
  PhysicalObject<dim, T>::translate(PhysicalObject::Vector const & vec)
{
    m_position += vec;
}
template <size_u dim, typename T>
ObjectBehaviourFlags
  PhysicalObject<dim, T>::getFlags() const
{
    return m_flags;
}
template <size_u dim, typename T>
ObjectBehaviourFlags
  PhysicalObject<dim, T>::resetFlags(ObjectBehaviourFlags flags)
{
    m_flags = flags;
}
template <size_u dim, typename T>
bool
  PhysicalObject<dim, T>::hasFlags(ObjectBehaviourFlags flags) const
{
    return static_cast<int>(m_flags) & static_cast<int>(flags);
}
template <size_u dim, typename T>
void
  PhysicalObject<dim, T>::raiseFlags(ObjectBehaviourFlags flags, bool add)
{
    if (add)
    {
        m_flags = m_flags | flags;
    }
    else // remove
    {
        m_flags = m_flags xor (m_flags & flags);
    }
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICALOBJECT_INL
