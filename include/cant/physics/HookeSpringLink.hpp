
#ifndef CANTINA_PHYSICS_HOOKESPRINGLINK_HPP
#define CANTINA_PHYSICS_HOOKESPRINGLINK_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/common/types.hpp>

#include <cant/physics/StaticPhysicalLink.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
class HookeSpringLink : public StaticPhysicalLink<dim, T, 2>
{
   public:
    /** -- typedef -- **/
    typedef StaticPhysicalLink<dim, T, 2> Link;
    typedef typename Link::Object Object;
    typedef typename Link::Vector Vector;

    /** -- methods -- **/
    HookeSpringLink(T k, T l0, ShPtr<Object> o1, ShPtr<Object> o2);

    CANT_INLINE void setStiffness(T k);
    CANT_INLINE void setRestLength(T l0);

   private:
    /** -- methods -- **/
    void getDeltaForceInternal(Stream<ShPtr<Object>> const & objects, Stream<Vector> & deltaForces) const override;

    /** -- fields -- **/
    T m_k; // stiffness factor
    T m_l0; // rest length
};


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/HookeSpringLink.inl>

#endif  // CANTINA_PHYSICS_HOOKESPRINGLINK_HPP
