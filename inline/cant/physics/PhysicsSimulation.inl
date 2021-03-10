
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
      m_kineticObjects(std::make_shared<Stream<ShPtr<Kinetic>>>()),
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
     * todo!
    m_collisionDetector.detectCollisions();
    m_collisionSolver.solveCollisions(m_collisionDetector.getCollisions());
    */
    for (auto & object : *m_kineticObjects)
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
    forceField->setObjects(m_kineticObjects);
    addForce(std::move(forceField));
}

template <size_u dim, typename T>
void
  PhysicsSimulation<dim, T>::addRigidObject(ShPtr<Rigid>  rigidObject, typename Detector::LayerKey layer)
{
    // add collider to collision detection routine.
    m_collisionDetector.addCollider(rigidObject->getCollider(), layer);
    // add object to kinetic objects.
    m_kineticObjects->push_back(std::move(rigidObject));
}

template <size_u dim, typename T>
void
  PhysicsSimulation<dim, T>::addDynamicObject(
    ShPtr<Dynamic> dynamicObject)
{
    m_kineticObjects->push_back(std::move(dynamicObject));
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICSSIMULATION_INL