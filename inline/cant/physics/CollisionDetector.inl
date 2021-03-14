
#ifndef CANTINA_PHYSICS_COLLISIONDETECTOR_INL
#define CANTINA_PHYSICS_COLLISIONDETECTOR_INL

#pragma once

#include <algorithm>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
CollisionDetector<dim, T>::CollisionDetector()
    : m_colliders(), m_enabledLayers(), m_enabled(true),
      m_collisions(), m_broadCollisions()
{}

template <size_u dim, typename T>
CANT_INLINE void
  CollisionDetector<dim, T>::detectCollisions()
{
    m_broadCollisions.clear();
    std::swap(m_collisions, m_previousCollisions);
    m_collisions.clear();
    if (m_enabled)
    {
        detectBroadPhase();
        detectNarrowPhase();
    }
}

template <size_u dim, typename T>
CANT_INLINE void
  CollisionDetector<dim, T>::addCollider(WPtr<Collider> collider, LayerKey layer)
{
    m_colliders.try_emplace(layer, Stream<WPtr<Collider>>());
    m_enabledLayers.try_emplace(layer, true);
    m_colliders.find(layer)->second.emplace_back(collider);
}

template <size_u dim, typename T>
void
  CollisionDetector<dim, T>::detectBroadPhase()
{
    for (auto & [layer, colliders] : m_colliders)
    {
        if (!m_enabledLayers.at(layer))
        {
            continue;
        }
        Stream<ShPtr<Collider>> sharedColliders;

        // fill shared colliders
        sharedColliders.reserve(m_colliders.size());
        for (auto it = colliders.begin(); it != colliders.end(); ++it)
        {
            ShPtr<Collider> collider = it->lock();
            if (!collider)
            {
                colliders.erase(it);
            }
            else
            {
                sharedColliders.push_back(collider);
            }
        }

        // check for intersections without duplicate.
        for (auto it1 = sharedColliders.begin(); it1 != sharedColliders.end() - 1; ++it1)
        {
            auto & col1 = *it1;
            for (auto it2 = it1 + 1; it2 != sharedColliders.end(); ++it2)
            {
                auto & col2 = *it2;
                // should not check for collisions between static colliders.
                const bool shouldCheck = !(col1->isStatic() && col2->isStatic());
                if (shouldCheck && col1->isIntersectingAABB(col2))
                {
                    m_broadCollisions.push_back(typename Collision::CollisionPair(col1, col2));
                }
            }
        }
    }
}

template <size_u dim, typename T>
void
  CollisionDetector<dim, T>::detectNarrowPhase()
{
    m_collisions.reserve(m_broadCollisions.size());
    // record all collisions
    for (auto & broadPhaseCollision : m_broadCollisions)
    {
        ShPtr<Collider> & col1 = broadPhaseCollision.first;
        ShPtr<Collider> & col2 = broadPhaseCollision.second;
        auto intersection = col1->getIntersection(col2);
        if (intersection.has_value())
        {
            m_collisions.emplace_back(std::move(broadPhaseCollision), std::move(intersection.value()));
        }
    }

    // update the states of the collisions from the previous ones.
    for (auto const & previous : m_previousCollisions)
    {
        // look for it in the updated collisions
        auto it = std::find_if(
          m_collisions.begin(), m_collisions.end(),
          [&previous](Collision const & collision)
          {
            return previous.haveSameColliders(collision);
            }
        );

        // deciding whether it's still happening, and updating phase if so.
        typename Collision::ContactPhase const previousPhase = previous.getPhase();

        if (it == m_collisions.end())
        {
            // if we can no longer find it, it's either because it has left or because it was leaving last time.
            if (previousPhase != Collision::eLeave)
            {
                m_collisions.push_back(previous);
                m_collisions.back().setPhase(Collision::eLeave);
            }
        }
        else
        {
            it->setPhase(Collision::eStay);
        }
    }
    //
}

template <size_u dim, typename T>
CANT_INLINE Stream<typename CollisionDetector<dim, T>::Collision> &
            CollisionDetector<dim, T>::getCollisions()
{
    return m_collisions;
}
template <size_u dim, typename T>
void
  CollisionDetector<dim, T>::setEnabled(LayerKey layer, bool enable)
{
    m_enabledLayers.at(layer) = enable;
}

template <size_u dim, typename T>
void
CollisionDetector<dim, T>::setEnabled(bool enable)
{
    m_enabled = enable;
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_COLLISIONDETECTOR_INL