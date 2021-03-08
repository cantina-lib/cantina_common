
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

template <size_u dim, typename T>
class PhysicsSimulation
{
    /** -- constraints -- **/
    static_assert(std::is_arithmetic_v<T>);
    // static_assert(std::is_floating_point_v<T>); ?

   public:
    /** -- typedefs -- **/
    typedef CollisionDetector<dim, T> Detector;
    typedef CollisionSolver<dim, T>   Solver;

    typedef PhysicalForce<dim, T> Force;
    typedef PhysicalForceField<dim, T> ForceField;

    typedef RigidObject<dim, T> Rigid;
    typedef KineticObject<dim, T> Object;

    typedef KineticUpdater<dim, T> Updater;

    /** -- methods -- **/
    PhysicsSimulation();

    void
      stepDelta(T dt);

    void
      addForce(ShPtr<Force> force);
    /**
     * Same as addForce for ForceFields, but also links the objects of the simulation to it.
     * @param forceField
     */
    void addForceField(ShPtr<ForceField> forceField);

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