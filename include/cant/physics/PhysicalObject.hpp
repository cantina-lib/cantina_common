
#ifndef CANTINA_PHYSICS_PHYSICALOBJECT_HPP
#define CANTINA_PHYSICS_PHYSICALOBJECT_HPP

#pragma once

#include <cant/common/types.hpp>
#include <cant/common/memory.hpp>

#include <cant/physics/Positionable.hpp>

#include <cant/physics/PhysicalState.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

    template <typename Len_T, size_u dim>
    class PhysicalObject : public Positionable<Len_T, dim>
    {
    public:
        /** -- methods -- **/
        virtual void translate(typename Positionable<Len_T, dim>::Vector const& vec) = 0;
    };

    template <class State, typename Len_T, size_u dim>
    class PhysicalObjectTrait : public  PhysicalObject<Len_T, dim>
    {
        /** -- constraints -- **/
        static_assert(std::is_convertible_v<State*, PhysicalState<Len_T, dim>*>);

    public:
        /** -- methods -- **/
        CANT_EXPLICIT PhysicalObjectTrait(UPtr<State> state);

        // implemented from PhysicalObject
        void translate(typename PhysicalState<Len_T, dim>::Vector const& vec) override;

        // implemented from Positionable
        void setPosition(typename PhysicalState<Len_T, dim>::Position position) override;
        CANT_NODISCARD typename PhysicalState<Len_T, dim>::Position const& getPosition() const override;

    protected:
        /** -- fields -- **/
        // pointer here to remind myself that it could be shared.
        UPtr<State> m_state;
    };

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/PhysicalObject.inl>

#endif //CANTINA_PHYSICS_PHYSICALOBJECT_HPP
