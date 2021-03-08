
#ifndef CANTINA_PHYSICS_RIGIDOBJECT_INL
#define CANTINA_PHYSICS_RIGIDOBJECT_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
RigidObject<dim, T>::RigidObject(UPtr<Shape> shape)
    : KineticObject<dim, T>(), m_collider(std::make_shared<Collider>(this, std::move(shape)))
{}

template <size_u dim, typename T>
CANT_INLINE WPtr<typename RigidObject<dim, T>::Collider>
            RigidObject<dim, T>::getCollider() const
{
    return m_collider;
}

    template<size_u dim, typename T>
    RigidObject<dim, T>::RigidObject(T mass, UPtr <RigidObject::Shape> shape)
        : KineticObject<dim, T>(mass), m_collider(std::make_shared<Collider>(this, std::move(shape)))
    {

    }

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_RIGIDOBJECT_INL
