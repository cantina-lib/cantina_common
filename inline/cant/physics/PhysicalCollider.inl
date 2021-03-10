
#ifndef CANTINA_PHYSICS_PHYSICALCOLLIDER_INL
#define CANTINA_PHYSICS_PHYSICALCOLLIDER_INL

#pragma once

#include <cant/maths/approx.hpp>

#include <cant/common/macro.hpp>
#include <cant/physics/PhysicalCollider.hpp>

CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
CANT_INLINE typename PhysicalCollider<dim, T>::Vector
  PhysicalCollider<dim, T>::getVectorToClosestRim(Position const & pos) const
{
    Vector vec  = getVectorToCentre(pos);
    T  dist = vec.getNorm();
    if (maths::approx<T>::equal(static_cast<T>(0), dist))
    {
        // if the position is basically at the centre of the shape
        // return whatever direction, but not null!
        vec = Position();
        vec.template set<0>(static_cast<T>(1));
    }
    else
    {
        // else get the direction.
        vec = vec.getNormalised();
    }
    return (-m_shape->getRadius()) * vec;
}

template <size_u dim, typename T>
CANT_INLINE typename PhysicalCollider<dim, T>::Vector
  PhysicalCollider<dim, T>::getVectorToCentre(Position const & pos) const
{
    // ditto.
    return m_shape->getVectorToCentreObject(pos - m_owner->getPosition());
}

template <size_u dim, typename T>
CANT_INLINE typename PhysicalCollider<dim, T>::Position
  PhysicalCollider<dim, T>::getCentre() const
{
    return m_shape->getCentreObject() + m_owner->getPosition();
}

template <size_u dim, typename T>
CANT_INLINE void
  PhysicalCollider<dim, T>::translate(Vector const & vec)
{
    m_owner->setPosition(m_owner->getPosition() + vec);
}
template <size_u dim, typename T>
CANT_INLINE bool
  PhysicalCollider<dim, T>::intersectsAABB(ShPtr<PhysicalCollider> const & other) const
{
    const AABB aabb1 = AABB(this->getCentre(),
                            this->m_shape->getRadius() * maths::Vector<dim, T>::fill(static_cast<T>(1)));
    const AABB aabb2 = AABB(other->getCentre(),
                            other->m_shape->getRadius() * maths::Vector<dim, T>::fill(static_cast<T>(1)));
    return aabb1.intersects(aabb2);
}

template <size_u dim, typename T>
CANT_INLINE bool
  PhysicalCollider<dim, T>::intersects(ShPtr<PhysicalCollider> const & other) const
{
    Position const & c1 = this->getCentre();
    Position const & c2 = other->getCentre();
    return m_shape->intersectsObject(other->m_shape, c1, c2);
}

template <size_u dim, typename T>
CANT_INLINE bool
  PhysicalCollider<dim, T>::isStatic() const
{
    return m_owner->isStatic();
}

template <size_u dim, typename T>
PhysicalCollider<dim, T>::PhysicalCollider(Collidable<dim, T> * owner, ShPtr<Shape> shape)
    : m_owner(owner), m_shape(std::move(shape))
{}
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

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICALCOLLIDER_INL