
#ifndef CANTINA_PHYSICS_PHYSICALFORCE_HPP
#define CANTINA_PHYSICS_PHYSICALFORCE_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/common/types.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
class KineticObject;

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
class PhysicalForce
{
   public:
    /** -- typedef -- **/
    typedef KineticObject<Len_T, Mass_T, Time_T, dim> Object;
    typedef typename Object::Acceleration             DeltaForce;  // kg.m.s-2, or N

    /** -- methods -- **/
    PhysicalForce();
    virtual ~PhysicalForce() = default;

    /**
     * Fills force buffer of all linked objects once.
     */
    virtual void apply() const = 0;

    /**
     *
     * @return Whether this force should be discarded.
     */
    CANT_NODISCARD
    bool
      hasExpired() const;

   protected:
    /** -- methods -- **/
    void
      signalExpired() const;

   private:

    /** -- fields -- **/
    mutable bool m_hasEnded;
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/PhysicalForce.inl>

#endif  // CANTINA_PHYSICS_PHYSICALFORCE_HPP
