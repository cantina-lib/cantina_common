
#ifndef CANTINA_PHYSICS_PHYSICSSIMULATION_INL
#define CANTINA_PHYSICS_PHYSICSSIMULATION_INL

#pragma once

#include <cant/maths/approx.hpp>

#include <cant/physics/LeapfrogUpdater.hpp>

#include <cant/common/macro.hpp>
#include <cant/physics/PhysicsSimulation.hpp>

CANTINA_PHYSICS_NAMESPACE_BEGIN

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
PhysicsSimulation<Len_T, Mass_T, Time_T, dim>::PhysicsSimulation()
    : m_updater(std::make_unique<LeapfrogUpdater<Len_T, Mass_T, Time_T, dim>>()),
    m_collisionDetector(),
    m_collisionSolver(),
    m_objects(std::make_shared<Stream<ShPtr<Object>>>()),
    m_forces()
{}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
CANT_INLINE void
  PhysicsSimulation<Len_T, Mass_T, Time_T, dim>::stepDelta(Time_T dt)
{
    for (auto it = m_forces.begin(); it != m_forces.end(); ++it)
    {
        auto & force = *it;
        if (!force->hasExpired())
        {
            force->apply();
        }
        else
        {
            it = m_forces.erase(it);
        }
    }
    // Before setting the positions from velocity, check for collisions,
    // and adjust velocity if necessary!
    /*
    m_collisionDetector.detectCollisions();
    m_collisionSolver.solveCollisions(m_collisionDetector.getCollisions());
    */
    for (ShPtr<Object> & object : *m_objects)
    {
        m_updater->stepDelta(object, dt);
    }
}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
void
  PhysicsSimulation<Len_T, Mass_T, Time_T, dim>::addForce(UPtr<Force> forceField)
{
    m_forces.push_back(std::move(forceField));
}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
void
PhysicsSimulation<Len_T, Mass_T, Time_T, dim>::addForceField(UPtr<PhysicsSimulation::ForceField> forceField)
{
    forceField->setObjects(m_objects);
    addForce(std::move(forceField));
}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
void
  PhysicsSimulation<Len_T, Mass_T, Time_T, dim>::addRigidObject(ShPtr<PhysicsSimulation::Rigid> & rigidObject,
                                                                typename Detector::LayerKey               layer)
{
    m_objects->push_back(static_cast<ShPtr<Object>>(rigidObject));

    // add to collision detection
    m_collisionDetector.addCollider(rigidObject->getCollider(), layer);
}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
void
  PhysicsSimulation<Len_T, Mass_T, Time_T, dim>::addKinematicObject(
    ShPtr<PhysicsSimulation::Object> & kinematicObject)
{
    m_objects->push_back(static_cast<ShPtr<Object>>(kinematicObject));
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICSSIMULATION_INL