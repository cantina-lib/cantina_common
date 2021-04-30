
#ifndef CANTINA_PHYSICS_KINETICOBJECT_INL
#define CANTINA_PHYSICS_KINETICOBJECT_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

    template <size_u dim, typename T>
    KineticObject<dim, T>::KineticObject()
      : m_flags(PhysicalObject<dim, T>::c_defaultObjectFlags)
    {}

    template <size_u dim, typename T>
    ObjectBehaviourFlags
    KineticObject<dim, T>::getFlags() const
    {
        return m_flags;
    }
    template <size_u dim, typename T>
    void
    KineticObject<dim, T>::resetFlags(ObjectBehaviourFlags flags)
    {
        m_flags = flags;
    }
    template <size_u dim, typename T>
    bool
    KineticObject<dim, T>::hasFlag(FObjectBehaviour flag) const
    {
        return static_cast<int>(m_flags) & static_cast<int>(flag);
    }
    template <size_u dim, typename T>
    void
    KineticObject<dim, T>::raiseFlags(ObjectBehaviourFlags flags, bool add)
    {
        if (add)
        {
            m_flags = m_flags | flags;
        }
        else // remove
        {
            m_flags = m_flags xor (m_flags & flags);
        }
    }
CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_KINETICOBJECT_INL
