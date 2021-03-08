
#ifndef CANTINA_PHYSICS_HOOKSPRINGLINK_HPP
#define CANTINA_PHYSICS_HOOKSPRINGLINK_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/common/types.hpp>

#include <cant/physics/StaticPhysicalLink.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
class HookeSpringLink : public StaticPhysicalLink<Len_T, Mass_T, Time_T, dim, 2>
{
   public:
    /** -- typedef -- **/
    typedef StaticPhysicalLink<Len_T, Mass_T, Time_T, dim, 2> Link;
    typedef typename Link::Object Object;
    typedef typename Link::DeltaForce DeltaForce;

    /** -- methods -- **/
    HookeSpringLink(Mass_T k, Len_T l0, ShPtr<Object> & o1, ShPtr<Object> & o2);

   private:
    /** -- methods -- **/
    void getDeltaForceInternal(Stream<ShPtr<Object>> const & objects, Stream<DeltaForce> & deltaForces) const override;

    /** -- fields -- **/
    // I picked the types at random...
    // not so sure using different types for mass, time and length
    // is a good idea any more.
    Mass_T m_k;
    Len_T m_l0;
};


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/HookSpringLink.inl>

#endif  // CANTINA_PHYSICS_PHYSICALFORCE_HPP
