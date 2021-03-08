
#ifndef CANTINA_PHYSICS_PHYSICALFORCE_HPP
#define CANTINA_PHYSICS_PHYSICALFORCE_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/common/types.hpp>

#include <cant/physics/KineticObject.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <size_u dim, typename T>
class PhysicalForce
{
   public:
    /** -- typedef -- **/
    typedef KineticObject<dim, T> Object;
    typedef typename Object::Vector Vector;

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
