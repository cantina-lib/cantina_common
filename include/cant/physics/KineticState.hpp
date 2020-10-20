
#ifndef CANTINA_PHYSICS_KINETICSTATE_HPP
#define CANTINA_PHYSICS_KINETICSTATE_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/physics/Kinetic.hpp>
#include <cant/physics/PhysicalState.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

    template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    class KineticState :
            public PhysicalState<Len_T, dim>,
            public Kinetic<Len_T, Mass_T, dim>
    {
        /** -- contraints -- **/
        static_assert(std::is_arithmetic_v<Len_T>);
        static_assert(std::is_floating_point_v<Mass_T>);
        static_assert(std::is_floating_point_v<Time_T>);

    public:
        /** -- typedefs -- **/

        typedef typename Positionable<Len_T, dim>::Position Position;
        typedef typename Kinetic<Len_T, Mass_T, dim>::Velocity Velocity;     // m.s-1
        typedef Velocity Acceleration; // m.s-2

        typedef Position DeltaForce; // kg.m.s-2, or N

        // Where we will store the accumulated force
        struct KineticBuffer
        {
            DeltaForce deltaForce;
        };


        /** -- methods -- **/
        KineticState(Mass_T mass, Position position);
        CANT_EXPLICIT KineticState(Mass_T mass);

        // updates the velocity, then position, from the accumulated force
        // in the buffer, and clears the buffer.
        void stepDelta(Time_T dt);

        void addDeltaForce(DeltaForce const& dF);

        // implemented from Kinetic
        void setMass(Mass_T mass) override;
        CANT_NODISCARD Mass_T getInverseMass() const override;
        void setVelocity(Velocity velocity) override;
        CANT_NODISCARD Velocity const& getVelocity() const override;
        CANT_NODISCARD Acceleration const& getAcceleration() const override;


    private:
        /** -- methods -- **/

        void updateAccelerationFromAccumulatedForce();
        void updateVelocityFromAcceleration(Time_T dt);
        void updatePositionFromVelocity(Time_T dt);
        void clearAccumulatedDeltaForce();

        /** -- fields -- **/
        Mass_T        m_inverseMass;

        Velocity      m_velocity;
        Acceleration  m_acceleration;
        KineticBuffer m_buffer;

    };

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/KineticState.inl>

#endif //CANTINA_PHYSICS_KINETICSTATE_HPP
