
#ifndef CANTINA_PHYSICS_RIGIDOBJECT_INL
#define CANTINA_PHYSICS_RIGIDOBJECT_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
RigidObject<dim, T>::RigidObject(UPtr<Kinetic> object, ShPtr<Shape> shape)
    : m_object(std::move(object)),
      m_collider(std::make_shared<Collider>(this, shape)),
      m_inContactColliders()
{}

template <size_u dim, typename T>
CANT_INLINE WPtr<typename RigidObject<dim, T>::Collider>
            RigidObject<dim, T>::getCollider() const
{
    return m_collider;
}
template <size_u dim, typename T>
CANT_INLINE void
  RigidObject<dim, T>::setMass(T mass)
{
    m_object->setMass(mass);
}

template <size_u dim, typename T>
CANT_INLINE T
  RigidObject<dim, T>::getInverseMass() const
{
    return m_object->getInverseMass();
}

template <size_u dim, typename T>
CANT_INLINE void
  RigidObject<dim, T>::setVelocity(Vector velocity)
{
   m_object->setVelocity(std::move(velocity));
}

template <size_u dim, typename T>
CANT_INLINE typename RigidObject<dim, T>::Vector
  RigidObject<dim, T>::getVelocity() const
{
 return m_object->getVelocity();
}

template <size_u dim, typename T>
CANT_INLINE typename RigidObject<dim, T>::Vector
  RigidObject<dim, T>::getAcceleration() const
{
    return m_object->getAcceleration();
}
template <size_u dim, typename T>
CANT_INLINE void
  RigidObject<dim, T>::setPosition(Position position)
{
    m_object->setPosition(std::move(position));
}
template <size_u dim, typename T>
CANT_INLINE typename RigidObject<dim, T>::Position const &
  RigidObject<dim, T>::getPosition() const
{
    return m_object->getPosition();
}

template <size_u dim, typename T>
CANT_INLINE bool RigidObject<dim, T>::isStatic() const
{
    return m_object->hasFlags(FObjectBehaviour::fStaticObject);
}
template <size_u dim, typename T>
CANT_INLINE void
  RigidObject<dim, T>::addDeltaForce(Vector const & dF)
{
    m_object->addDeltaForce(dF);
}
template <size_u dim, typename T>
CANT_INLINE void
  RigidObject<dim, T>::updateVelocity(T dt)
{
    m_object->updateVelocity(dt);
}
template <size_u dim, typename T>
CANT_INLINE void
  RigidObject<dim, T>::updatePosition(T dt)
{
    m_object->updatePosition(dt);
}

template <size_u dim, typename T>
CANT_INLINE void
  RigidObject<dim, T>::clearForceBuffer()
{
    m_object->clearForceBuffer();
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_RIGIDOBJECT_INL
