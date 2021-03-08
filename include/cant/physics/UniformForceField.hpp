
#ifndef CANTINA_PHYSICS_UNIFORMFORCEFIELD_HPP
#define CANTINA_PHYSICS_UNIFORMFORCEFIELD_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/common/types.hpp>

#include <cant/physics/PhysicalForceField.hpp>

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
class UniformForceField : public PhysicalForceField<Len_T, Mass_T, Time_T, dim>
{
   public:
    /** -- typedef -- **/
    typedef PhysicalForceField<Len_T, Mass_T, Time_T, dim> ForceField;
    typedef typename ForceField::Object     Object;
    typedef typename ForceField::ObjectStream ObjectStream;
    typedef typename ForceField::DeltaForce DeltaForce;

    /** -- methods -- **/
    UniformForceField(ObjectStream & objects, DeltaForce vec);
    CANT_EXPLICIT UniformForceField(DeltaForce vec);

   private:
    /** -- methods -- **/
    // implemented from PhysicalForceField.
    CANT_NODISCARD DeltaForce getDeltaForce(ShPtr<Object> const & object) const final;

    /** -- fields -- **/
    DeltaForce m_vec;
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/UniformForceField.inl>

#endif  // CANTINA_PHYSICS_PHYSICALFORCE_HPP
