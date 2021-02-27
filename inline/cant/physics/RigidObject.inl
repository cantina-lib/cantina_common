
#ifndef CANTINA_PHYSICS_RIGIDOBJECT_INL
#define CANTINA_PHYSICS_RIGIDOBJECT_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
RigidObject<Len_T, Mass_T, Time_T, dim>::RigidObject(UPtr<Shape> shape)
    : KineticObject<Len_T, Mass_T, Time_T, dim>(), m_collider(std::make_shared<Collider>(this, std::move(shape)))
{}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
CANT_INLINE WPtr<typename RigidObject<Len_T, Mass_T, Time_T, dim>::Collider>
            RigidObject<Len_T, Mass_T, Time_T, dim>::getCollider() const
{
    return m_collider;
}

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    RigidObject<Len_T, Mass_T, Time_T, dim>::RigidObject(Mass_T mass, UPtr <RigidObject::Shape> shape)
        : KineticObject<Len_T, Mass_T, Time_T, dim>(mass), m_collider(std::make_shared<Collider>(this, std::move(shape)))
    {

    }

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_RIGIDOBJECT_INL
