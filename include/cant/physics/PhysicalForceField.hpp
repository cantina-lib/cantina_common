
#ifndef CANTINA_PHYSICS_PHYSICALFORCEFIELD_HPP
#define CANTINA_PHYSICS_PHYSICALFORCEFIELD_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/common/types.hpp>

#include <cant/physics/PhysicalForce.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

/**
 * Applies a force individually to all objects in the simulation.
 * Should hold a reference to the stream of objects used by the simulation.
 * @tparam Len_T
 * @tparam Mass_T
 * @tparam Time_T
 * @tparam dim
 */
template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
class PhysicalForceField : public PhysicalForce<Len_T, Mass_T, Time_T, dim>
{
   public:
    /** -- typedef -- **/
    typedef PhysicalForce<Len_T, Mass_T, Time_T, dim> Force;
    typedef typename Force::Object     Object;
    typedef typename Force::DeltaForce DeltaForce;
    typedef ShPtr<Stream<ShPtr<Object>>> ObjectStream;

    /** -- methods -- **/
    CANT_EXPLICIT PhysicalForceField(ObjectStream const & objects);
    PhysicalForceField();

    void setObjects(ObjectStream const & objects);

    void apply() const final;

   private:
    /** -- methods -- **/
    CANT_NODISCARD virtual DeltaForce getDeltaForce(ShPtr<Object> const & object) const = 0;

    /** -- fields -- **/
    ObjectStream m_objects;
};


CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/PhysicalForceField.inl>

#endif  // CANTINA_PHYSICS_PHYSICALFORCE_HPP
