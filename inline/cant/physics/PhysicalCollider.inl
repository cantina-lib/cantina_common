
#ifndef CANTINA_PHYSICS_PHYSICALCOLLIDER_INL
#define CANTINA_PHYSICS_PHYSICALCOLLIDER_INL

#pragma once

#include <cant/maths/approx.hpp>

#include <cant/common/macro.hpp>
#include <cant/physics/PhysicalCollider.hpp>

CANTINA_PHYSICS_NAMESPACE_BEGIN

    template<typename Len_T, typename Mass_T, size_u dim>
    CANT_INLINE
    typename PhysicalCollider<Len_T, Mass_T, dim>::Vector
    PhysicalCollider<Len_T, Mass_T, dim>::
    getVectorToClosestRim(Position const& pos) const
    {
        Vector vec = getVectorToCentre(pos);
        Len_T dist = vec.getNorm();
        if (maths::approx<Len_T>::equal(static_cast<Len_T>(0), dist))
        {
            // if the position is basically at the centre of the shape
            // return whatever direction, but not null!
            vec = Position();
            vec.template set<0>(static_cast<Len_T>(1));
        }
        else
        {
            // else get the direction.
            vec = vec.getNormalised();
        }
        return (- m_shape->getRadius()) * vec;
    }

    template<typename Len_T, typename Mass_T, size_u dim>
    CANT_INLINE
    typename PhysicalCollider<Len_T, Mass_T, dim>::Vector
    PhysicalCollider<Len_T, Mass_T, dim>::
    getVectorToCentre(Position const& pos) const
    {
        // ditto.
        return m_shape->getVectorToCentreObject(pos - m_owner->getPosition());
    }


    template<typename Len_T, typename Mass_T, size_u dim>
    CANT_INLINE
    typename PhysicalCollider<Len_T, Mass_T, dim>::Velocity const&
    PhysicalCollider<Len_T, Mass_T, dim>::
    getVelocity() const
    {
        return m_owner->getVelocity();
    }

    template<typename Len_T, typename Mass_T, size_u dim>
    CANT_INLINE
    Mass_T
    PhysicalCollider<Len_T, Mass_T, dim>::
    getInverseMass() const
    {
        return m_owner->getInverseMass();
    }

    template<typename Len_T, typename Mass_T, size_u dim>
    CANT_INLINE
    typename PhysicalCollider<Len_T, Mass_T, dim>::Position
    PhysicalCollider<Len_T, Mass_T, dim>::
    getCentre() const
    {
        return m_shape->getCentreObject() + m_owner->getPosition();
    }

    template<typename Len_T, typename Mass_T, size_u dim>
    CANT_INLINE
    void
    PhysicalCollider<Len_T, Mass_T, dim>::
    translate(Vector const& vec)
    {
        m_owner->setPosition(m_owner->getPosition() + vec);
    }

    template<typename Len_T, typename Mass_T, size_u dim>
    CANT_INLINE
    void
    PhysicalCollider<Len_T, Mass_T, dim>::
    setVelocity(Velocity velocity)
    {
        m_owner->setVelocity(std::move(velocity));
    }

    template<typename Len_T, typename Mass_T, size_u dim>
    CANT_INLINE
    bool
    PhysicalCollider<Len_T, Mass_T, dim>::
    intersectsAABB(ShPtr <PhysicalCollider> const& other) const
    {
        const AABB aabb1 = AABB
                (
                this->getCentre(),
                this->m_shape->getRadius() * maths::Vector<Len_T, dim>::fill(static_cast<Len_T>(1))
                );
        const AABB aabb2 = AABB
                (
                other->getCentre(),
                other->m_shape->getRadius() * maths::Vector<Len_T, dim>::fill(static_cast<Len_T>(1))
                );
        return aabb1.intersects(aabb2);
    }

    template<typename Len_T, typename Mass_T, size_u dim>
    CANT_INLINE
    bool
    PhysicalCollider<Len_T, Mass_T, dim>::
    intersects(ShPtr <PhysicalCollider> const& other) const
    {
        Position const& c1 = this->getCentre();
        Position const& c2 = other->getCentre();
        return m_shape->intersectsObject(other->m_shape, c1, c2);
    }


    template<typename Len_T, typename Mass_T, size_u dim>
    CANT_INLINE
    void
    PhysicalCollider<Len_T, Mass_T, dim>::
    setMass(Mass_T mass)
    {
        m_owner->setMass(mass);
    }

    template<typename Len_T, typename Mass_T, size_u dim>
    CANT_INLINE
    bool
    PhysicalCollider<Len_T, Mass_T, dim>::
    isStatic() const
    {
        return m_owner->isStatic();
    }


    template<typename Len_T, typename Mass_T, size_u dim>
    CANT_INLINE
    typename PhysicalCollider<Len_T, Mass_T, dim>::Acceleration const&
    PhysicalCollider<Len_T, Mass_T, dim>::
    getAcceleration() const
    {
        return m_owner->getAcceleration();
    }

    template<typename Len_T, typename Mass_T, size_u dim>
    PhysicalCollider<Len_T, Mass_T, dim>::
    PhysicalCollider(Collidable<Len_T, Mass_T, dim> * owner, UPtr<Shape> shape)
            : m_owner(owner),
              m_shape(std::move(shape))
    { }

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_PHYSICS_PHYSICALCOLLIDER_INL