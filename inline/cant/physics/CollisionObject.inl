
#ifndef CANTINA_PHYSICS_COLLISIONOBJECT_INL
#define CANTINA_PHYSICS_COLLISIONOBJECT_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <typename Len_T, typename Mass_T, size_u dim>
CollisionObject<Len_T, Mass_T, dim>::CollisionObject(UPtr<State> state, UPtr<Shape> shape)
    : PhysicalObjectTrait<State, Len_T, dim>(std::move(state)),
      m_collider(std::make_shared<Collider>(this, std::move(shape)))
{}

template <typename Len_T, typename Mass_T, size_u dim>
CANT_INLINE void
  CollisionObject<Len_T, Mass_T, dim>::setPosition(CollisionObject::Position position)
{
    PhysicalObjectTrait<PhysicalState<Len_T, dim>, Len_T, dim>::setPosition(std::move(position));
}

template <typename Len_T, typename Mass_T, size_u dim>
CANT_INLINE typename CollisionObject<Len_T, Mass_T, dim>::Position const &
  CollisionObject<Len_T, Mass_T, dim>::getPosition() const
{
    return PhysicalObjectTrait<PhysicalState<Len_T, dim>, Len_T, dim>::getPosition();
}

template <typename Len_T, typename Mass_T, size_u dim>
WPtr<typename CollisionObject<Len_T, Mass_T, dim>::Collider>
  CollisionObject<Len_T, Mass_T, dim>::getCollider() const
{
    return m_collider;
}

CANTINA_PHYSICS_NAMESPACE_END

#include <cant/common/undef_macro.hpp>
#endif  // CANTINA_PHYSICS_PHYSICALOBJECT_INL
