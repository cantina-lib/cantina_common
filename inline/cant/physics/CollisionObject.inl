
#ifndef CANTINA_PHYSICS_COLLISIONOBJECT_INL
#define CANTINA_PHYSICS_COLLISIONOBJECT_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
CollisionObject<dim, T>::CollisionObject(UPtr<Shape> shape)
    : StaticObject<dim, T>(), m_collider(std::make_shared<Collider>(this, std::move(shape)))
{}

template <size_u dim, typename T>
WPtr<typename CollisionObject<dim, T>::Collider>
  CollisionObject<dim, T>::getCollider() const
{
    return m_collider;
}

CANTINA_PHYSICS_NAMESPACE_END

#include <cant/common/undef_macro.hpp>
#endif  // CANTINA_PHYSICS_PHYSICALOBJECT_INL
