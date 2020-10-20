
#ifndef CANTINA_PHYSICS_RIGIDOBJECT_INL
#define CANTINA_PHYSICS_RIGIDOBJECT_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    RigidObject<Len_T, Mass_T, Time_T, dim>::
    RigidObject(UPtr<State> state, UPtr<Shape> shape)
        : KineticObject<Len_T, Mass_T, Time_T, dim>(std::move(state)),
        m_collider(std::make_shared<Collider>(this, std::move(shape)))
    { }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    void
    RigidObject<Len_T, Mass_T, Time_T, dim>::
    setPosition(RigidObject::Position position)
    {
            return KineticObject<Len_T, Mass_T, Time_T, dim>::setPosition(std::move(position));
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    typename RigidObject<Len_T, Mass_T, Time_T, dim>::Position const&
    RigidObject<Len_T, Mass_T, Time_T, dim>::
    getPosition() const
    {
        return KineticObject<Len_T, Mass_T, Time_T, dim>::getPosition();
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    void
    RigidObject<Len_T, Mass_T, Time_T, dim>::
    setMass(Mass_T mass)
    {
        KineticObject<Len_T, Mass_T, Time_T, dim>::setMass(mass);
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    Mass_T
    RigidObject<Len_T, Mass_T, Time_T, dim>::
    getInverseMass() const
    {
        return KineticObject<Len_T, Mass_T, Time_T, dim>::getInverseMass();
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    typename RigidObject<Len_T, Mass_T, Time_T, dim>::Velocity const&
    RigidObject<Len_T, Mass_T, Time_T, dim>::
    getVelocity() const
    {
        return KineticObject<Len_T, Mass_T, Time_T, dim>::getVelocity();
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    void
    RigidObject<Len_T, Mass_T, Time_T, dim>::
    setVelocity(RigidObject::Velocity velocity)
    {
        KineticObject<Len_T, Mass_T, Time_T, dim>::setVelocity(std::move(velocity));
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    WPtr <typename RigidObject<Len_T, Mass_T, Time_T, dim>::Collider>
    RigidObject<Len_T, Mass_T, Time_T, dim>::
    getCollider() const
    {
        return m_collider;
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    typename RigidObject<Len_T, Mass_T, Time_T, dim>::Acceleration const&
    RigidObject<Len_T, Mass_T, Time_T, dim>::
    getAcceleration() const
    {
        return KineticObject<Len_T, Mass_T, Time_T, dim>::getAcceleration();
    }

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_PHYSICS_RIGIDOBJECT_INL
