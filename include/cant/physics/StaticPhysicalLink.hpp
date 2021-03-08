
#ifndef CANTINA_PHYSICS_STATICPHYSICALLINK_HPP
#define CANTINA_PHYSICS_STATICPHYSICALLINK_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/common/types.hpp>

#include <cant/physics/WeakRefPhysicalForce.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim, size_u numberObjects>
class StaticPhysicalLink : public WeakRefPhysicalForce<Len_T, Mass_T, Time_T, dim>
{
   public:
    /** -- typedef -- **/
    typedef WeakRefPhysicalForce<Len_T, Mass_T, Time_T, dim> Force;
    typedef typename Force::Object     Object;
    typedef typename Force::DeltaForce DeltaForce;
    typedef Array<WPtr<Object>, numberObjects> ObjectRefArray;
    typedef Array<ShPtr<Object>, numberObjects> ObjectArray;

    /** -- methods -- **/
    CANT_EXPLICIT StaticPhysicalLink(ObjectArray objects);

    void getDeltaForce(Stream<ShPtr<Object>> const & objects, Stream<DeltaForce> & deltaForces) const final;

   private:
    /** -- methods -- **/
    virtual void getDeltaForceInternal(Stream<ShPtr<Object>> const & objects, Stream<DeltaForce> & deltaForces) const = 0;

    // Private inheritance from WeakRefPhysicalForce
    CANT_NODISCARD size_u getNumberObjects() const final;
    CANT_NODISCARD WPtr<Object> const * getObjects() const final;
    void cleanUp() override;

    /** -- fields -- **/
    ObjectRefArray m_objectRefs;
};


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/StaticPhysicalLink.inl>

#endif  // CANTINA_PHYSICS_PHYSICALFORCE_HPP
