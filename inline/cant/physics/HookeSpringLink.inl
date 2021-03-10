
#ifndef CANTINA_PHYSICS_HOOKESPRINGLINK_INL
#define CANTINA_PHYSICS_HOOKESPRINGLINK_INL

#pragma once

#include <cant/maths/approx.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template<size_u dim, typename T>
HookeSpringLink<dim, T>::HookeSpringLink(T k, T l0, ShPtr<Object> & o1, ShPtr<Object> & o2)
    : Link({ o1, o2 }), m_k(k), m_l0(l0)
{

}

template <size_u dim, typename T>
void
  HookeSpringLink<dim, T>::getDeltaForceInternal(const Stream<ShPtr<Object>> & objects, Stream<Vector> & deltaForces) const
{
    CANTINA_ASSERT(objects.size() == 2, "nnnn");
    CANTINA_ASSERT(deltaForces.size() == 2, "fdsl");

    Vector deltaP = (objects.at(0)->getPosition() - objects.at(1)->getPosition());
    T l = deltaP.getNorm();
    if (maths::approx<T>::equal(l, static_cast<T>(0.)))
    {
        return;
    }
    T deltaL =  l - m_l0;
    Vector f = (- m_k * deltaL) * deltaP.getNormalised();
    deltaForces.at(0) = f;
    deltaForces.at(1) = - f;
}

template <size_u dim, typename T>
void
  HookeSpringLink<dim, T>::setStiffness(T k)
{
    m_k = k;
}
template <size_u dim, typename T>
void
  HookeSpringLink<dim, T>::setRestLength(T l0)
{
    m_l0 = l0;
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICALFORCE_INL