
#ifndef CANTINA_PHYSICS_STATICOBJECT_INL
#define CANTINA_PHYSICS_STATICOBJECT_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
StaticObject<dim, T>::StaticObject(Position position)
    : m_position(std::move(position))
{
    // bad design decisions led to this.
    this->raiseFlags(FObjectBehaviour::fStaticObject, true);
}

template <size_u dim, typename T>
CANT_INLINE void
  StaticObject<dim, T>::setPosition(Position pos)
{
    m_position = std::move(pos);
}

template <size_u dim, typename T>
CANT_INLINE typename StaticObject<dim, T>::Position const &
  StaticObject<dim, T>::getPosition() const
{
    return m_position;
}

template <size_u dim, typename T>
CANT_INLINE void
  StaticObject<dim, T>::translate(Vector const & vec)
{
    m_position += vec;
}
CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_STATICOBJECT_INL
