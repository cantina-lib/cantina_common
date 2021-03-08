
#ifndef CANTINA_PHYSICS_WEAKREFPHYSICALFORCE_HPP
#define CANTINA_PHYSICS_WEAKREFPHYSICALFORCE_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/common/types.hpp>

#include <cant/physics/PhysicalForce.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
class WeakRefPhysicalForce : public PhysicalForce<Len_T, Mass_T, Time_T, dim>
{
   public:
    /** -- typedef -- **/
    typedef PhysicalForce<Len_T, Mass_T, Time_T, dim> Force;
    typedef typename Force::Object Object;
    typedef typename Object::Acceleration             DeltaForce;  // kg.m.s-2, or N

    /** -- methods -- **/
    WeakRefPhysicalForce();
    virtual ~WeakRefPhysicalForce() = default;

    /**
     * Fills force buffer of all linked objects once.
     */
    void apply() const final;

    /**
     * Removed all references to lost objects. Should be called before applying.
     * Will signal for expiration if necessary.
     */
    virtual void cleanUp() = 0;

   private:
    /** -- methods -- **/
    // All right, this definitely part of the shadier stuff I do on this project.
    // I want classes inheriting PhysicalForces to be able to store their objects
    // however is the most fitting. For instance most PhysicalLinks will apply on
    // only two objects. As such, I'd rather use an array than a vector,
    // but a particle system would use an arbitrary number of objects.
    // So these functions constitute a common interface between all derived classes.
    /**
     * @return the number of kinetic objects pointed to by the return of getObjects.
     */
    CANT_NODISCARD virtual size_u getNumberObjects() const = 0;
    /**
     * @return a pointer to a list of kinetic objects the force applies to
     */
     // mm probably the first and last time I use a bare pointer in combination with a smart one.
     // let's hope I figure a cleaner way to do this thing next time.
    CANT_NODISCARD virtual WPtr<Object> const * getObjects() const = 0;
    /**
     * Fills deltaForces vector with delta force to apply to each object in objects.
     * @param objects
     * @param deltaForces
     */
    virtual void getDeltaForce(Stream<ShPtr<Object>> const & objects, Stream<DeltaForce> & deltaForces) const = 0;
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/WeakRefPhysicalForce.inl>

#endif  // CANTINA_PHYSICS_PHYSICALFORCE_HPP
