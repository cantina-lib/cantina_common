
#ifndef CANTINA_PHYSICS_PHYSICSSIMULATION_INL
#define CANTINA_PHYSICS_PHYSICSSIMULATION_INL

#pragma once

#include <cant/maths/approx.hpp>

#include <cant/physics/LeapfrogUpdater.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
PhysicsSimulation<dim, T>::PhysicsSimulation()
    : m_updater(std::make_unique<LeapfrogUpdater<dim, T>>()),
    m_collisionDetector(),
    m_collisionSolver(),
    m_objects(std::make_shared<Stream<ShPtr<Object>>>()),
    m_forces()
{}

template <size_u dim, typename T>
CANT_INLINE void
  PhysicsSimulation<dim, T>::stepDelta(T dt)
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

template <size_u dim, typename T>
void
  PhysicsSimulation<dim, T>::addForce(ShPtr<Force> forceField)
{
    m_forces.push_back(std::move(forceField));
}

template <size_u dim, typename T>
void
PhysicsSimulation<dim, T>::addForceField(ShPtr<ForceField> forceField)
{
    forceField->setObjects(m_objects);
    addForce(std::move(forceField));
}

template <size_u dim, typename T>
void
  PhysicsSimulation<dim, T>::addRigidObject(ShPtr<Rigid>  rigidObject, typename Detector::LayerKey layer)
{
    m_objects->push_back(std::move(static_cast<ShPtr<Object>>(rigidObject)));

    // add to collision detection
    m_collisionDetector.addCollider(rigidObject->getCollider(), layer);
}

template <size_u dim, typename T>
void
  PhysicsSimulation<dim, T>::addKinematicObject(
    ShPtr<Object> kinematicObject)
{
    m_objects->push_back(std::move(static_cast<ShPtr<Object>>(kinematicObject)));
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICSSIMULATION_INL