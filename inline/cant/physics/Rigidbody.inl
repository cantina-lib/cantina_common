
#ifndef CANTINA_PHYSICS_RIGIDOBJECT_INL
#define CANTINA_PHYSICS_RIGIDOBJECT_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
Rigidbody<dim, T>::Rigidbody(UPtr<Object> object, UPtr<Shape> shape)
    : m_object(std::move(object)), m_collider(std::make_shared<Collider>(this, std::move(shape)))
{}

template <size_u dim, typename T>
CANT_INLINE WPtr<typename Rigidbody<dim, T>::Collider>
            Rigidbody<dim, T>::getCollider() const
{
    return m_collider;
}
template <size_u dim, typename T>
CANT_INLINE void
  Rigidbody<dim, T>::setMass(T mass)
{
    m_object->setMass(mass);
}

template <size_u dim, typename T>
CANT_INLINE T
  Rigidbody<dim, T>::getInverseMass() const
{
    return m_object->getInverseMass();
}

template <size_u dim, typename T>
CANT_INLINE void
  Rigidbody<dim, T>::setVelocity(Vector velocity)
{
   m_object->setVelocity(std::move(velocity));
}

template <size_u dim, typename T>
CANT_INLINE typename Rigidbody<dim, T>::Vector const &
  Rigidbody<dim, T>::getVelocity() const
{
 return m_object->getVelocity();
}

template <size_u dim, typename T>
CANT_INLINE typename Rigidbody<dim, T>::Vector
  Rigidbody<dim, T>::getAcceleration() const
{
    return m_object->getAcceleration();
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_RIGIDOBJECT_INL
