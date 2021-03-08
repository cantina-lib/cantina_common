
#ifndef CANTINA_PHYSICS_PHYSICSSIMULATION_HPP
#define CANTINA_PHYSICS_PHYSICSSIMULATION_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/common/types.hpp>

#include <cant/physics/CollisionDetector.hpp>
#include <cant/physics/CollisionSolver.hpp>

#include <cant/physics/KineticUpdater.hpp>

#include <cant/physics/CollisionObject.hpp>
#include <cant/physics/KineticObject.hpp>
#include <cant/physics/RigidObject.hpp>

#include <cant/physics/PhysicalForce.hpp>
#include <cant/physics/PhysicalForceField.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
class PhysicsSimulation
{
    /** -- constraints -- **/
    static_assert(std::is_arithmetic_v<Len_T>);
    static_assert(std::is_floating_point_v<Mass_T>);
    static_assert(std::is_floating_point_v<Time_T>);

   public:
    /** -- typedefs -- **/
    typedef CollisionDetector<Len_T, Mass_T, dim> Detector;
    typedef CollisionSolver<Len_T, Mass_T, dim>   Solver;

    typedef PhysicalForce<Len_T, Mass_T, Time_T, dim> Force;
    typedef PhysicalForceField<Len_T, Mass_T, Time_T, dim> ForceField;

    typedef RigidObject<Len_T, Mass_T, Time_T, dim> Rigid;
    typedef KineticObject<Len_T, Mass_T, Time_T, dim> Object;

    typedef KineticUpdater<Len_T, Mass_T, Time_T, dim> Updater;

    /** -- methods -- **/
    PhysicsSimulation();

    void
      stepDelta(Time_T dt);

    void
      addForce(UPtr<Force> force);
    /**
     * Same as addForce for ForceFields, but also links the objects of the simulation to it.
     * @param forceField
     */
    void addForceField(UPtr<ForceField> forceField);

    void
      addRigidObject(ShPtr<Rigid> & rigidObject, typename Detector::LayerKey layer);
    void
      addKinematicObject(ShPtr<Object> & kinematicObject);

   private:
    /** -- fields -- **/
    UPtr<Updater> m_updater;

    Detector m_collisionDetector;
    Solver   m_collisionSolver;

    ShPtr<Stream<ShPtr<Object>>> m_objects;

    Stream<ShPtr<Force>> m_forces;
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/PhysicsSimulation.inl>

#endif  // CANTINA_PHYSICS_PHYSICSSIMULATION_HPP