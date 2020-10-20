
#ifndef CANTINA_PHYSICS_PHYSICALOBJECT_INL
#define CANTINA_PHYSICS_PHYSICALOBJECT_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

    template <class State, typename Len_T, size_u dim>
    CANT_INLINE
    void
    PhysicalObjectTrait<State, Len_T, dim>::
    setPosition(typename PhysicalState<Len_T, dim>::Position position)
    {
    	m_state->setPosition(std::move(position));
    }

    template <class State, typename Len_T, size_u dim>
    CANT_INLINE
    void
    PhysicalObjectTrait<State, Len_T, dim>::
    translate(typename PhysicalState<Len_T, dim>::Vector const& vec)
    {
        m_state->translate(vec);
    }

    template <class State, typename Len_T, size_u dim>
    CANT_INLINE
    typename PhysicalState<Len_T, dim>::Position const&
    PhysicalObjectTrait<State, Len_T, dim>::
    getPosition() const
    {
    	return m_state->getPosition();
    }

    template <class State, typename Dim_T, size_u dim>
    CANT_INLINE
    PhysicalObjectTrait<State, Dim_T, dim>::
    PhysicalObjectTrait(UPtr<State> state)
        : m_state(std::move(state))
    {

    }


CANTINA_PHYSICS_NAMESPACE_END

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_PHYSICS_PHYSICALOBJECT_INL
