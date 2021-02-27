
#ifndef CANTINA_PHYSICS_COLLISIONOBJECT_INL
#define CANTINA_PHYSICS_COLLISIONOBJECT_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <typename Len_T, size_u dim>
CollisionObject<Len_T, dim>::CollisionObject(UPtr<Shape> shape)
    : PhysicalObject<Len_T, dim>(), m_collider(std::make_shared<Collider>(this, std::move(shape)))
{}

template <typename Len_T, size_u dim>
WPtr<typename CollisionObject<Len_T, dim>::Collider>
  CollisionObject<Len_T, dim>::getCollider() const
{
    return m_collider;
}

CANTINA_PHYSICS_NAMESPACE_END

#include <cant/common/undef_macro.hpp>
#endif  // CANTINA_PHYSICS_PHYSICALOBJECT_INL
