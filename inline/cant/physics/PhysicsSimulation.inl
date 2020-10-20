
#ifndef CANTINA_PHYSICS_PHYSICSSIMULATION_INL
#define CANTINA_PHYSICS_PHYSICSSIMULATION_INL

#pragma once

#include <cant/maths/approx.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN


    template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    PhysicsSimulation<Len_T, Mass_T, Time_T, dim>::
    PhysicsSimulation()
        : m_collisionDetector(),
        m_collisionSolver(),
        m_forceFields()
    {

    }


    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    CANT_INLINE
    void
    PhysicsSimulation<Len_T, Mass_T, Time_T, dim>::
    stepDelta(Time_T dt)
    {
        stepObjectsDelta(dt);
        stepForceFieldsDelta(dt);


        m_collisionDetector.detectCollisions();
        m_collisionSolver.solveCollisions(m_collisionDetector.getCollisions());
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    void
    PhysicsSimulation<Len_T, Mass_T, Time_T, dim>::
    stepObjectsDelta(Time_T dt)
    {
        for (auto& object : m_rigidObjects)
        {
            for (auto const& forceField : m_forceFields)
            {
                object->addDeltaForceField(forceField);
            }
            object->stepDelta(dt);
        }
        // force fields are ignored by kinematic objects!
        for (auto& object : m_kinematicObjects)
        {
            object->stepDelta(dt);
        }
        // static objects don't change!
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    void
    PhysicsSimulation<Len_T, Mass_T, Time_T, dim>::
    stepForceFieldsDelta(Time_T dt)
    {
        for (auto it = m_forceFields.begin(); it != m_forceFields.end(); ++it)
        {
            ShPtr<ForceField>& forceField = *it;
            if (forceField->hasEnded())
            {
                m_forceFields.erase(it);
            }
            else
            {
                forceField->stepDelta(dt);
            }
        }
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    void
    PhysicsSimulation<Len_T, Mass_T, Time_T, dim>::
    addForceField(UPtr<ForceField> forceField)
    {
        m_forceFields.push_back(std::move(forceField));
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    void
    PhysicsSimulation<Len_T, Mass_T, Time_T, dim>::
    addRigidObject(ShPtr <PhysicsSimulation::DynamicObject> &rigidObject, typename Detector::LayerKey layer)
    {
        m_rigidObjects.push_back(rigidObject);

        // add to collision detection
        m_collisionDetector.addCollider(rigidObject->getCollider(), layer);
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    void
    PhysicsSimulation<Len_T, Mass_T, Time_T, dim>::
    addKinematicObject(ShPtr <PhysicsSimulation::DynamicObject> &kinematicObject, typename Detector::LayerKey layer)
    {
        m_kinematicObjects.push_back(kinematicObject);

        // same thing.
        m_collisionDetector.addCollider(kinematicObject->getCollider(), layer);
    }

    template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
    void
    PhysicsSimulation<Len_T, Mass_T, Time_T, dim>::
    addStaticObject(ShPtr <PhysicsSimulation::StaticObject> &staticObject, typename Detector::LayerKey layer)
    {
        m_staticObjects.push_back(staticObject);
        // ditto.
        m_collisionDetector.addCollider(staticObject->getCollider(), layer);
    }

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_PHYSICS_PHYSICSSIMULATION_INL