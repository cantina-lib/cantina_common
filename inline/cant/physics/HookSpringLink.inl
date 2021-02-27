
#ifndef CANTINA_PHYSICS_HOOKSPRINGLINK_INL
#define CANTINA_PHYSICS_HOOKSPRINGLINK_INL

#pragma once

#include <cant/maths/approx.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template<typename Len_T, typename Mass_T, typename Time_T, size_u dim>
HookSpringLink<Len_T, Mass_T, Time_T, dim>::HookSpringLink(Mass_T k, Len_T l0, ShPtr<Object> & o1, ShPtr<Object> & o2)
    : Link({ o1, o2 }), m_k(k), m_l0(l0)
{

}

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
void
HookSpringLink<Len_T, Mass_T, Time_T, dim>::getDeltaForceInternal(const Stream <ShPtr<Object>> &objects,
                                                                  Stream <DeltaForce> &deltaForces
) const
{
    CANTINA_ASSERT(objects.size() == 2, "nnnn");
    CANTINA_ASSERT(deltaForces.size() == 2, "fdsl");

    auto deltaP = (objects.at(0)->getPosition() - objects.at(1)->getPosition());
    Len_T l = deltaP.getNorm();
    if (maths::approx<Len_T>::equal(l, static_cast<Len_T>(0.)))
    {
        return;
    }
    Len_T deltaL =  l - m_l0;
    DeltaForce f = (- m_k * deltaL) * deltaP.getNormalised();
    deltaForces.at(0) = f;
    deltaForces.at(1) = - f;
}

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_PHYSICS_PHYSICALFORCE_INL