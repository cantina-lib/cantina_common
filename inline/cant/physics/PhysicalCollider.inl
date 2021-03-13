
#ifndef CANTINA_PHYSICS_PHYSICALCOLLIDER_INL
#define CANTINA_PHYSICS_PHYSICALCOLLIDER_INL

#pragma once

#include <cant/maths/approx.hpp>

#include <cant/common/macro.hpp>
#include <cant/physics/PhysicalCollider.hpp>

CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
PhysicalCollider<dim, T>::PhysicalCollider(Collidable<dim, T> * owner, ShPtr<Shape> shape, Position centre)
  : m_owner(owner), m_shape(std::move(shape)), m_centre(std::move(centre))
{}

template <size_u dim, typename T>
CANT_INLINE typename PhysicalCollider<dim, T>::Position
  PhysicalCollider<dim, T>::getCentreWorld() const
{
    return m_centre + m_owner->getPosition();
}

template <size_u dim, typename T>
CANT_INLINE ShPtr<typename PhysicalCollider<dim, T>::Shape> const &
PhysicalCollider<dim, T>::getShape() const
{
    return m_shape;
}

template <size_u dim, typename T>
CANT_INLINE void
  PhysicalCollider<dim, T>::translate(Vector const & vec)
{
    m_owner->setPosition(m_owner->getPosition() + vec);
}
template <size_u dim, typename T>
CANT_INLINE bool
  PhysicalCollider<dim, T>::isIntersectingAABB(ShPtr<PhysicalCollider> const & other) const
{
    const AABB aabb1 = AABB(this->getCentreWorld(),
                            this->m_shape->getRadius() * maths::Vector<dim, T>::fill(static_cast<T>(1)));
    const AABB aabb2 = AABB(other->getCentreWorld(),
                            other->m_shape->getRadius() * maths::Vector<dim, T>::fill(static_cast<T>(1)));
    return aabb1.intersects(aabb2);
}

template <size_u dim, typename T>
CANT_INLINE Optional<typename PhysicalCollider<dim, T>::Intersection>
  PhysicalCollider<dim, T>::getIntersection(ShPtr<PhysicalCollider<dim, T>> const & other) const
{
    return m_shape->getIntersection(other->m_shape, this->getCentreWorld(), other->getCentreWorld());
}

template <size_u dim, typename T>
CANT_INLINE bool
  PhysicalCollider<dim, T>::isStatic() const
{
    return m_owner->isStatic();
}

template <size_u dim, typename T>
CANT_INLINE void
  PhysicalCollider<dim, T>::setPosition(Position position)
{
    m_owner->setPosition(std::move(position));
}
template <size_u dim, typename T>
CANT_INLINE typename PhysicalCollider<dim, T>::Position const &
  PhysicalCollider<dim, T>::getPosition() const
{
    return m_owner->getPosition();
}
template <size_u dim, typename T>
typename PhysicalCollider<dim, T>::Vector
  PhysicalCollider<dim, T>::getVelocity() const
{
    return m_owner->getVelocity();
}
template <size_u dim, typename T>
void
  PhysicalCollider<dim, T>::setVelocity(Vector velocity)
{
    return m_owner->setVelocity(std::move(velocity));
}

template <size_u dim, typename T>
typename PhysicalCollider<dim, T>::Vector
  PhysicalCollider<dim, T>::getAcceleration() const
{
    return m_owner->getAcceleration();
}

template <size_u dim, typename T>
void
  PhysicalCollider<dim, T>::setMass(T mass)
{
    return m_owner->setMass(mass);
}

template <size_u dim, typename T>
T
  PhysicalCollider<dim, T>::getInverseMass() const
{
    return m_owner->getInverseMass();
}

template <size_u dim, typename T>
void
  PhysicalCollider<dim, T>::addDeltaForce(Vector const & dF)
{
    m_owner->addDeltaForce(dF);
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICALCOLLIDER_INL