
#ifndef CANTINA_PHYSICS_PHYSICALCOLLISION_HPP
#define CANTINA_PHYSICS_PHYSICALCOLLISION_HPP

#pragma once

#include <cant/common/types.hpp>
#include <cant/common/memory.hpp>

#include <cant/physics/Positionable.hpp>
#include <cant/physics/Kinetic.hpp>

#include <cant/physics/PhysicalCollider.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

    template <typename Len_T, typename Mass_T, size_u dim>
    class PhysicalCollision
    {
    public:
        /** -- typedefs -- **/
        typedef typename Positionable<Len_T, dim>::Position Position;
        typedef typename Positionable<Len_T, dim>::Vector Vector;

        typedef typename Kinetic<Len_T, Mass_T, dim>::Velocity Velocity;
        typedef typename Kinetic<Len_T, Mass_T, dim>::Acceleration Acceleration;

        typedef PhysicalCollider<Len_T, Mass_T, dim> Collider;
        typedef Pair<ShPtr<Collider>, ShPtr<Collider>> CollisionPair;

        /** -- structs -- **/
        enum ContactPhase
        {
            eEnter = 0,
            eStay  = 1,
            eLeave = 2,
        };

        // see:
        // https://www.myphysicslab.com/engine2D/collision-en.html
        struct Contact
        {

            // vectors from centre of mass to contact point in Object coordinates of max collider.
            Position rap;

            // normals
             Vector n;

            // no angular velocity.

            // velocities of impact points of min and max colliders
            Velocity vbp;
            Velocity vap;

            Len_T e;

            // impulse
            Len_T impulse;
        };

        /** -- methods -- **/
        CANT_EXPLICIT PhysicalCollision(CollisionPair pair);

        void computeCollision();

        CANT_NODISCARD ShPtr<Collider>& getColliderMax();
        CANT_NODISCARD ShPtr<Collider>& getColliderMin();

        CANT_NODISCARD bool haveSameColliders(PhysicalCollision const& other) const;


        void setPhase(ContactPhase phase);
        CANT_NODISCARD ContactPhase getPhase() const;

    private:
        /** -- methods -- **/
        void setCollidersVelocities();
        void setCollidersSupport();
        void computeContact();

        void sortColliders();

        /** -- fields -- **/
        CollisionPair m_pair;

        ContactPhase m_phase;

        Contact m_contact;

        // constants
        static CANT_CONSTEXPR Len_T c_restitution = static_cast<Len_T>(0.); // dimensionless.
    };


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/PhysicalCollision.inl>

#endif //CANTINA_PHYSICS_PHYSICALCOLLISION_HPP