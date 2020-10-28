
#ifndef CANTINA_PHYSICS_CUSTOMFORCEFIELD_HPP
#define CANTINA_PHYSICS_CUSTOMFORCEFIELD_HPP

#pragma once

#include <cant/common/functor.hpp>
#include <cant/common/memory.hpp>
#include <cant/common/types.hpp>

#include <cant/physics/PhysicalForceField.hpp>

#include <cant/common/macro.hpp>
CANTINA_PHYSICS_NAMESPACE_BEGIN

template <typename Len_T, typename Mass_T, typename Time_T, size_u dim>
class CustomForceField : public PhysicalForceField<Len_T, Mass_T, Time_T, dim>
{
   public:
    /** -- typedef -- **/
    typedef PhysicalForceField<Len_T, Mass_T, Time_T, dim> ForceField;

    typedef Functor<typename ForceField::DeltaForce(UPtr<typename ForceField::State> const &, Time_T dt)>
      DeltaForceFunctor;

    /** -- methods -- **/
    CANT_EXPLICIT
    CustomForceField(DeltaForceFunctor func);

    //  implementation of PhysicalForceField
    CANT_NODISCARD
    typename ForceField::DeltaForce
      getDeltaForce(UPtr<typename ForceField::State> const & previous) const final;

   private:
    /** -- fields -- **/
    DeltaForceFunctor m_func;
};

CANTINA_PHYSICS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/physics/CustomForceField.inl>

#endif  // CANTINA_PHYSICS_CUSTOMFORCEFIELD_HPP
