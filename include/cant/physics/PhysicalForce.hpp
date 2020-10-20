
#ifndef CANTINA_PHYSICS_PHYSICALFORCE_HPP
#define CANTINA_PHYSICS_PHYSICALFORCE_HPP

#pragma once

#include <cant/common/types.hpp>
#include <cant/common/memory.hpp>

#include <cant/physics/KineticState.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

    template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    class PhysicalForce
    {
    public:
        /** -- typedef -- **/
        typedef KineticState<Len_T, Mass_T, Time_T, dim> State; // kg.m.s-2, or N
        typedef typename State::Position DeltaForce; // kg.m.s-2, or N

        /** -- methods -- **/
        PhysicalForce();
        virtual ~PhysicalForce() = default;

        void stepDelta(Time_T dt);
        // Get delta force (delta work?) for the force field.
        // As such, does not compute the resulting acceleration,
        // even though it takes the state as an argument.
        // However, it is necessary in cases like gravity,
        // were the acceleration is a function of distance,
        // we would need to know the position of the object it is applied to.
        // should only be called by PhysicalState.
        CANT_NODISCARD virtual DeltaForce getDeltaForce(UPtr<State> const& previous) const = 0;

        CANT_NODISCARD
        bool hasEnded() const;

    protected:
        /** -- methods -- **/
        void signalEnded() const;

        /** -- fields -- **/
        Time_T m_dt;

    private:
        /** -- fields -- **/
        mutable bool m_hasEnded;

    };


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/PhysicalForce.inl>

#endif //CANTINA_PHYSICS_PHYSICALFORCE_HPP
