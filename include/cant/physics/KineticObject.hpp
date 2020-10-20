
#ifndef CANTINA_PHYSICS_KINETICOBJECT_HPP
#define CANTINA_PHYSICS_KINETICOBJECT_HPP

#pragma once

#include <cant/common/types.hpp>
#include <cant/common/memory.hpp>

#include <cant/physics/PhysicalObject.hpp>

#include <cant/physics/Kinetic.hpp>

#include <cant/physics/KineticState.hpp>
#include <cant/physics/PhysicalAppliedForce.hpp>
#include <cant/physics/PhysicalForceField.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

    template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    class KineticObject :
            public PhysicalObjectTrait<KineticState<Len_T, Mass_T, Time_T, dim>, Len_T, dim>,
            public Kinetic<Len_T, Mass_T, dim>
    {
    public:
        /** -- typedef -- **/
        typedef PhysicalAppliedForce<Len_T, Mass_T, Time_T, dim> AppliedForce;
        typedef PhysicalForceField<Len_T, Mass_T, Time_T, dim> ForceField;
        typedef KineticState<Len_T, Mass_T, Time_T, dim> State;

        typedef typename Kinetic<Len_T, Mass_T, dim>::Velocity Velocity;
        typedef typename Kinetic<Len_T, Mass_T, dim>::Acceleration Acceleration;

        /** -- methods -- **/
        CANT_EXPLICIT KineticObject(UPtr<State> state);
        // applying work of forces on the object
        // and so update its state.
        // should only be called by the simulation.
        void stepDelta(Time_T dt);

        // respectively adds or removes applied force on the object.
        void addAppliedForce(UPtr<AppliedForce> force);

        // adds delta force from force field
        void addDeltaForceField(ShPtr<ForceField> const& forceField);

        // implemented from Kinetic
        void setMass(Mass_T mass) override;
        CANT_NODISCARD Mass_T getInverseMass() const override;
        /*
         * IMPORTANT
         * Only collision processes should
         * set the velocity and acceleration by hand
         * it should otherwise be updated with the acceleration.
         */
        void setVelocity(Velocity velocity) override;
        CANT_NODISCARD Velocity const& getVelocity() const override;
        CANT_NODISCARD Acceleration const& getAcceleration() const override;

    private:
        /** -- methods -- **/
        void clearAppliedForces();

        /** -- fields -- **/
        UStream<AppliedForce> m_appliedForce;
    };


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/KineticObject.inl>

#endif //CANTINA_PHYSICS_KINETICOBJECT_HPP
