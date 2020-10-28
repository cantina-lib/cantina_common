
#ifndef CANTINA_PHYSICS_PHYSICSSIMULATION_HPP
#define CANTINA_PHYSICS_PHYSICSSIMULATION_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/common/types.hpp>

#include <cant/physics/CollisionDetector.hpp>
#include <cant/physics/CollisionSolver.hpp>

#include <cant/physics/CollisionObject.hpp>
#include <cant/physics/RigidObject.hpp>

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

    typedef PhysicalForceField<Len_T, Mass_T, Time_T, dim> ForceField;

    typedef RigidObject<Len_T, Mass_T, Time_T, dim> DynamicObject;
    typedef CollisionObject<Len_T, Mass_T, dim>     StaticObject;

    /** -- methods -- **/
    PhysicsSimulation();

    void
      stepDelta(Time_T dt);

    void
      addForceField(UPtr<ForceField> forceField);

    void
      addRigidObject(ShPtr<DynamicObject> & rigidObject, typename Detector::LayerKey layer);
    void
      addKinematicObject(ShPtr<DynamicObject> & kinematicObject, typename Detector::LayerKey layer);
    void
      addStaticObject(ShPtr<StaticObject> & staticObject, typename Detector::LayerKey layer);

   private:
    /** -- methods -- **/
    void
      stepObjectsDelta(Time_T dt);
    void
      stepForceFieldsDelta(Time_T dt);

    /** -- fields -- **/
    Detector m_collisionDetector;
    Solver   m_collisionSolver;

    Stream<ShPtr<DynamicObject>> m_rigidObjects;
    Stream<ShPtr<DynamicObject>> m_kinematicObjects;
    Stream<ShPtr<StaticObject>>  m_staticObjects;

    Stream<ShPtr<ForceField>> m_forceFields;
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/PhysicsSimulation.inl>

#endif  // CANTINA_PHYSICS_PHYSICSSIMULATION_HPP